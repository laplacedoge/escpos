#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>

#include "config.h"

#include "bytestream.h"
#include "frontend.h"
#include "scanner.h"


#ifdef CONF_USE_GLOBAL_LOG_LEVEL
    #define LOG_LEVEL CONF_GLOBAL_LOG_LEVEL
#else
    #define LOG_LEVEL 5
#endif

#define LOG_TAG                     "FEND"

#if LOG_LEVEL > LOG_NONE
    #define FEND_LOG(format, ...)   CONF_LOG(LOG_TAG, format, ##__VA_ARGS__)
#else
    #define FEND_LOG(format, ...)
#endif

#if LOG_LEVEL >= LOG_ERROR
    #define LOG_E(format, ...)      FEND_LOG(format, ##__VA_ARGS__)
#else
    #define LOG_E(format, ...)
#endif

#if LOG_LEVEL >= LOG_WARN
    #define LOG_W(format, ...)      FEND_LOG(format, ##__VA_ARGS__)
#else
    #define LOG_W(format, ...)
#endif

#if LOG_LEVEL >= LOG_INFO
    #define LOG_I(format, ...)      FEND_LOG(format, ##__VA_ARGS__)
#else
    #define LOG_I(format, ...)
#endif

#if LOG_LEVEL >= LOG_DEBUG
    #define LOG_D(format, ...)      FEND_LOG(format, ##__VA_ARGS__)
#else
    #define LOG_D(format, ...)
#endif

#if LOG_LEVEL >= LOG_ASSERT
    #define ASSERT(expr)            CONF_ASSERT(LOG_TAG, expr)
#else
    #define ASSERT(expr)
#endif

typedef enum fend_cmd_category {
    FEND_CMD_HT     = 0x09,
    FEND_CMD_LF     = 0x0A,
    FEND_CMD_FF     = 0x0C,
    FEND_CMD_CR     = 0x0D,
    FEND_CMD_SO     = 0x0E,
    FEND_CMD_ESC    = 0x1B,
    FEND_CMD_FS     = 0x1C,
    FEND_CMD_GS     = 0x1D,
    FEND_CMD_US     = 0x1F,
} fend_cmd_category_t;

struct fend_ctx {
    struct fend_ctx_conf {
        escpos_cmd_cb_tab_t cmd_cb_tab;
        escpos_u32_t raw_stm_cap;
    } conf;
    bstm_ctx *raw_stm;
};

#define FEND_RAW_STM_CAP_MIN        1024

#define FEND_RDWR_RETRY_PERIOD_MS   10

#define FEND_TIMEOUT_INFINITE       0
#define FEND_TIMEOUT_SHORT          100
#define FEND_TIMEOUT_LONG          1000

static escpos_u64_t fend_get_timestamp_ms(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (escpos_u64_t)tv.tv_sec * 1000 + (escpos_u64_t)tv.tv_usec / 1000;
}

escpos_res_t fend_init(fend_ctx_t **ctx, fend_conf_t *conf) {
    fend_ctx_t *fend_ctx;
    bstm_ctx *mod_bstm_ctx;
    bstm_conf mod_bstm_conf;
    bstm_res mod_bstm_res;

    ASSERT(ctx != NULL);
    ASSERT(conf != NULL);

    if (conf->raw_stm_cap < FEND_RAW_STM_CAP_MIN) {
        LOG_E("raw stream capacity is too small, use default value.");

        return ESCPOS_ERR_BAD_CONF;
    }
    mod_bstm_conf.cap_size = conf->raw_stm_cap;

    mod_bstm_res = bstm_new(&mod_bstm_ctx, &mod_bstm_conf);
    if (mod_bstm_res != BSTM_OK) {
        LOG_E("failed to create raw stream, error code: %d.", (int)mod_bstm_res);

        return ESCPOS_ERR;
    }

    fend_ctx = (fend_ctx_t *)malloc(sizeof(fend_ctx_t));
    if (fend_ctx == NULL) {
        bstm_del(mod_bstm_ctx);

        LOG_E("failed to allocate memory for frontend context.");

        return ESCPOS_ERR_NO_MEM;
    }

    fend_ctx->raw_stm = mod_bstm_ctx;
    fend_ctx->conf.cmd_cb_tab = conf->cmd_cb_tab;
    fend_ctx->conf.raw_stm_cap = conf->raw_stm_cap;

    *ctx = fend_ctx;

    return ESCPOS_OK;
}

escpos_res_t fend_deinit(fend_ctx_t *ctx) {
    ASSERT(ctx != NULL);

    bstm_del(ctx->raw_stm);
    free(ctx);

    return ESCPOS_OK;
}

escpos_res_t fend_fill(fend_ctx_t *ctx, const void *buff, escpos_u32_t size) {
    bstm_res mod_bstm_res;

    ASSERT(ctx != NULL);
    ASSERT(buff != NULL);

    if (size == 0) {
        return ESCPOS_OK;
    }

    mod_bstm_res = bstm_write(ctx->raw_stm, buff, size);
    if (mod_bstm_res != BSTM_OK) {
        LOG_E("failed to write to raw stream, error code: %d.", (int)mod_bstm_res);

        if (mod_bstm_res == BSTM_ERR_NO_SPA) {
            return ESCPOS_ERR_NO_SPA;
        } else {
            return ESCPOS_ERR;
        }
    }

    return ESCPOS_OK;
}

/**
 * @brief read data from raw stream.
 * 
 * @param ctx frontend context.
 * @param buff buffer to store read data.
 * @param size size of data to read.
 * @param timeout timeout in milliseconds, when timeout is 0,
 *                this function will block until data is ready.
*/
static escpos_res_t fend_stm_read(fend_ctx_t *ctx, void *buff, escpos_u32_t size, escpos_u32_t timeout) {
    bstm_stat mod_bstm_stat;
    bstm_res mod_bstm_res;
    uint64_t end_time;

    ASSERT(ctx != NULL);
    ASSERT(buff != NULL);

    if (size == 0) {
        return ESCPOS_OK;
    }

    if (timeout == 0) {
        while (true) {
            bstm_status(ctx->raw_stm, &mod_bstm_stat);

            if (mod_bstm_stat.used_size >= size) {
                break;
            }

            usleep(1000 * FEND_RDWR_RETRY_PERIOD_MS);
        }
    } else {
        end_time = fend_get_timestamp_ms() + timeout;

        while (true) {
            bstm_status(ctx->raw_stm, &mod_bstm_stat);

            if (mod_bstm_stat.used_size >= size) {
                break;
            }

            if (fend_get_timestamp_ms() >= end_time) {
                return ESCPOS_ERR_TIMEOUT;
            }

            usleep(1000 * FEND_RDWR_RETRY_PERIOD_MS);
        }
    }

    mod_bstm_res = bstm_read(ctx->raw_stm, buff, size);
    if (mod_bstm_res != BSTM_OK) {
        LOG_E("failed to read from raw stream, error code: %d.", (int)mod_bstm_res);

        if (mod_bstm_res == BSTM_ERR_NO_DAT) {
            return ESCPOS_ERR_NO_DAT;
        } else {
            return ESCPOS_ERR;
        }
    }

    return ESCPOS_OK;
}

static escpos_res_t fend_assign(fend_ctx_t *ctx, escpos_cmd_cb_tab_t *cmd_cb_tab, escpos_u8_t cmd) {
    escpos_res_t res;

    ASSERT(cmd_cb_tab != NULL);

    switch (cmd) {
        case FEND_CMD_HT: {
            res = scan_cmd_cb_HT(ctx->raw_stm, cmd_cb_tab->cmd_cb_HT);
        } break;

        case FEND_CMD_LF: {
            res = scan_cmd_cb_LF(ctx->raw_stm, cmd_cb_tab->cmd_cb_LF);
        } break;

        case FEND_CMD_FF: {
            res = scan_cmd_cb_FF(ctx->raw_stm, cmd_cb_tab->cmd_cb_FF);
        } break;

        case FEND_CMD_CR: {
            res = scan_cmd_cb_CR(ctx->raw_stm, cmd_cb_tab->cmd_cb_CR);
        } break;

        case FEND_CMD_SO: {
            res = scan_cmd_cb_SO(ctx->raw_stm, cmd_cb_tab->cmd_cb_SO);
        } break;

        case FEND_CMD_ESC: {
            escpos_u8_t sub;

            res = fend_stm_read(ctx, &sub, 1, FEND_TIMEOUT_SHORT);
            if (res != ESCPOS_OK) {
                return res;
            }

            switch (sub) {
                case '@': {
                    res = scan_cmd_cb_ESC_at(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_at);
                } break;

                case 'J': {
                    res = scan_cmd_cb_ESC_J(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_J);
                } break;

                case 'd': {
                    res = scan_cmd_cb_ESC_d(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_d);
                } break;

                case '!': {
                    res = scan_cmd_cb_ESC_exclamation(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_exclamation);
                } break;

                case 'M': {
                    res = scan_cmd_cb_ESC_M(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_M);
                } break;

                case '-': {
                    res = scan_cmd_cb_ESC_minus(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_minus);
                } break;

                case 'E': {
                    res = scan_cmd_cb_ESC_E(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_E);
                } break;

                case 'V': {
                    res = scan_cmd_cb_ESC_V(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_V);
                } break;

                case '$': {
                    res = scan_cmd_cb_ESC_dollar(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_dollar);
                } break;

                case 'D': {
                    res = scan_cmd_cb_ESC_D(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_D);
                } break;

                case '2': {
                    res = scan_cmd_cb_ESC_2(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_2);
                } break;

                case '3': {
                    res = scan_cmd_cb_ESC_3(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_3);
                } break;

                case ' ': {
                    res = scan_cmd_cb_ESC_SP(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_SP);
                } break;

                case 'a': {
                    res = scan_cmd_cb_ESC_a(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_a);
                } break;

                case '*': {
                    res = scan_cmd_cb_ESC_asterisk(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_asterisk);
                } break;

                case 'Z': {
                    res = scan_cmd_cb_ESC_Z(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_Z);
                } break;

                case 't': {
                    res = scan_cmd_cb_ESC_t(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_t);
                } break;

                case 'R': {
                    res = scan_cmd_cb_ESC_R(ctx->raw_stm, cmd_cb_tab->cmd_cb_ESC_R);
                } break;

                default: {
                    return ESCPOS_ERR_BAD_SUB;
                } break;
            }
        } break;

        case FEND_CMD_FS: {
            escpos_u8_t sub;

            res = fend_stm_read(ctx, &sub, 1, FEND_TIMEOUT_SHORT);
            if (res != ESCPOS_OK) {
                return res;
            }

            switch (sub) {
                case 'P': {
                    res = scan_cmd_cb_FS_P(ctx->raw_stm, cmd_cb_tab->cmd_cb_FS_P);
                } break;

                case '&': {
                    res = scan_cmd_cb_FS_ampersand(ctx->raw_stm, cmd_cb_tab->cmd_cb_FS_ampersand);
                } break;

                case '.': {
                    res = scan_cmd_cb_FS_dot(ctx->raw_stm, cmd_cb_tab->cmd_cb_FS_dot);
                } break;

                case 'U': {
                    res = scan_cmd_cb_FS_U(ctx->raw_stm, cmd_cb_tab->cmd_cb_FS_U);
                } break;

                default: {
                    return ESCPOS_ERR_BAD_SUB;
                } break;
            }
        } break;

        case FEND_CMD_GS: {
            escpos_u8_t sub;

            res = fend_stm_read(ctx, &sub, 1, FEND_TIMEOUT_SHORT);
            if (res != ESCPOS_OK) {
                return res;
            }

            switch (sub) {
                case 0x0C: {
                    res = scan_cmd_cb_GS_FF(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_FF);
                } break;

                case 0x99: {
                    res = scan_cmd_cb_GS_H99(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_H99);
                } break;

                case 'B': {
                    res = scan_cmd_cb_GS_B(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_B);
                } break;

                case 'L': {
                    res = scan_cmd_cb_GS_L(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_L);
                } break;

                case '*': {
                    res = scan_cmd_cb_GS_asterisk(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_asterisk);
                } break;

                case '/': {
                    res = scan_cmd_cb_GS_forwardslash(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_forwardslash);
                } break;

                case 'h': {
                    res = scan_cmd_cb_GS_h(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_h);
                } break;

                case 'w': {
                    res = scan_cmd_cb_GS_w(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_w);
                } break;

                case 'H': {
                    res = scan_cmd_cb_GS_H(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_H);
                } break;

                case 'f': {
                    res = scan_cmd_cb_GS_f(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_f);
                } break;

                case 'k': {
                    res = scan_cmd_cb_GS_k(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_k);
                } break;

                case 'Z': {
                    res = scan_cmd_cb_GS_Z(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_Z);
                } break;

                case '\'': {
                    res = scan_cmd_cb_GS_singlequote(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_singlequote);
                } break;

                case '"': {
                    res = scan_cmd_cb_GS_doublequote(ctx->raw_stm, cmd_cb_tab->cmd_cb_GS_doublequote);
                } break;

                default: {
                    return ESCPOS_ERR_BAD_SUB;
                } break;
            }
        } break;

        case FEND_CMD_US: {
            escpos_u8_t sub;

            res = fend_stm_read(ctx, &sub, 1, FEND_TIMEOUT_SHORT);
            if (res != ESCPOS_OK) {
                return res;
            }

            switch (sub) {
                case 'f': {
                    res = scan_cmd_cb_US_f(ctx->raw_stm, cmd_cb_tab->cmd_cb_US_f);
                } break;

                case 'q': {
                    res = scan_cmd_cb_US_q(ctx->raw_stm, cmd_cb_tab->cmd_cb_US_q);
                } break;

                case '\x73': {
                    escpos_u8_t data[3];

                    res = fend_stm_read(ctx, data, 3, FEND_TIMEOUT_SHORT);
                    if (res != ESCPOS_OK) {
                        return res;
                    }

                    if (data[0] != 0x42 ||
                        data[2] != 0x50) {
                        return ESCPOS_ERR_BAD_SUB;
                    }

                    if (data[1] == 0x72) {
                        res = scan_cmd_cb_US_sBrPH1FH73H42H72H50(ctx->raw_stm, cmd_cb_tab->cmd_cb_US_sBrPH1FH73H42H72H50);
                    } else if (data[1] == 0x73) {
                        res = scan_cmd_cb_US_sBrP(ctx->raw_stm, cmd_cb_tab->cmd_cb_US_sBrP);
                    } else {
                        return ESCPOS_ERR_BAD_SUB;
                    }
                } break;

                default: {
                    return ESCPOS_ERR_BAD_SUB;
                } break;
            }
        } break;

        default: {
            return ESCPOS_ERR_BAD_CMD;
        } break;
    }

    return res;
}

escpos_res_t fend_proc(fend_ctx_t *ctx) {
    escpos_u8_t cmd;
    escpos_res_t res;

    ASSERT(ctx != NULL);

    while (true) {
        res = fend_stm_read(ctx, &cmd, 1, FEND_TIMEOUT_SHORT);
        if (res != ESCPOS_ERR_TIMEOUT) {
            continue;
        }

        fend_assign(ctx, &ctx->conf.cmd_cb_tab, cmd);
    }
    
}

