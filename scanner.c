#include "scanner.h"

#include "config.h"

#ifdef CONF_USE_GLOBAL_LOG_LEVEL
    #define LOG_LEVEL CONF_GLOBAL_LOG_LEVEL
#else
    #define LOG_LEVEL 5
#endif

#define LOG_TAG                     "SCAN"

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

escpos_res_t scan_cmd_cb_ESC_at(bstm_ctx *raw_stm, bend_cmd_cb_ESC_at_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_FF(bstm_ctx *raw_stm, bend_cmd_cb_FF_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_SO(bstm_ctx *raw_stm, bend_cmd_cb_SO_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_LF(bstm_ctx *raw_stm, bend_cmd_cb_LF_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_CR(bstm_ctx *raw_stm, bend_cmd_cb_CR_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_J(bstm_ctx *raw_stm, bend_cmd_cb_ESC_J_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_d(bstm_ctx *raw_stm, bend_cmd_cb_ESC_d_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_HT(bstm_ctx *raw_stm, bend_cmd_cb_HT_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_FF(bstm_ctx *raw_stm, bend_cmd_cb_GS_FF_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_H99(bstm_ctx *raw_stm, bend_cmd_cb_GS_H99_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_ESC_exclamation(bstm_ctx *raw_stm, bend_cmd_cb_ESC_exclamation_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_exclamation(bstm_ctx *raw_stm, bend_cmd_cb_GS_exclamation_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_M(bstm_ctx *raw_stm, bend_cmd_cb_ESC_M_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_minus(bstm_ctx *raw_stm, bend_cmd_cb_ESC_minus_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_E(bstm_ctx *raw_stm, bend_cmd_cb_ESC_E_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_B(bstm_ctx *raw_stm, bend_cmd_cb_GS_B_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_V(bstm_ctx *raw_stm, bend_cmd_cb_ESC_V_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_ESC_dollar(bstm_ctx *raw_stm, bend_cmd_cb_ESC_dollar_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_D(bstm_ctx *raw_stm, bend_cmd_cb_ESC_D_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_2(bstm_ctx *raw_stm, bend_cmd_cb_ESC_2_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_3(bstm_ctx *raw_stm, bend_cmd_cb_ESC_3_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_SP(bstm_ctx *raw_stm, bend_cmd_cb_ESC_SP_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_a(bstm_ctx *raw_stm, bend_cmd_cb_ESC_a_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_L(bstm_ctx *raw_stm, bend_cmd_cb_GS_L_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_ESC_asterisk(bstm_ctx *raw_stm, bend_cmd_cb_ESC_asterisk_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_asterisk(bstm_ctx *raw_stm, bend_cmd_cb_GS_asterisk_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_forwardslash(bstm_ctx *raw_stm, bend_cmd_cb_GS_forwardslash_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_FS_P(bstm_ctx *raw_stm, bend_cmd_cb_FS_P_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_GS_h(bstm_ctx *raw_stm, bend_cmd_cb_GS_h_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_w(bstm_ctx *raw_stm, bend_cmd_cb_GS_w_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_H(bstm_ctx *raw_stm, bend_cmd_cb_GS_H_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_f(bstm_ctx *raw_stm, bend_cmd_cb_GS_f_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_k(bstm_ctx *raw_stm, bend_cmd_cb_GS_k_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_Z(bstm_ctx *raw_stm, bend_cmd_cb_GS_Z_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_Z(bstm_ctx *raw_stm, bend_cmd_cb_ESC_Z_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_GS_singlequote(bstm_ctx *raw_stm, bend_cmd_cb_GS_singlequote_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_GS_doublequote(bstm_ctx *raw_stm, bend_cmd_cb_GS_doublequote_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_FS_ampersand(bstm_ctx *raw_stm, bend_cmd_cb_FS_ampersand_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_FS_dot(bstm_ctx *raw_stm, bend_cmd_cb_FS_dot_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_FS_U(bstm_ctx *raw_stm, bend_cmd_cb_FS_U_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_t(bstm_ctx *raw_stm, bend_cmd_cb_ESC_t_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_ESC_R(bstm_ctx *raw_stm, bend_cmd_cb_ESC_R_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_US_f(bstm_ctx *raw_stm, bend_cmd_cb_US_f_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_US_q(bstm_ctx *raw_stm, bend_cmd_cb_US_q_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}


escpos_res_t scan_cmd_cb_US_sBrPH1FH73H42H72H50(bstm_ctx *raw_stm, bend_cmd_cb_US_sBrPH1FH73H42H72H50_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}

escpos_res_t scan_cmd_cb_US_sBrP(bstm_ctx *raw_stm, bend_cmd_cb_US_sBrP_t cmd_cb) {
    ASSERT(raw_stm != NULL);

    return ESCPOS_OK;
}
