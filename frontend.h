#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#include "common.h"

typedef struct fend_ctx fend_ctx_t;

typedef struct fend_conf {
    escpos_cmd_cb_tab_t cmd_cb_tab;
    escpos_u32_t raw_stm_cap;
} fend_conf_t;

escpos_res_t fend_init(fend_ctx_t **ctx, fend_conf_t *conf);

escpos_res_t fend_deinit(fend_ctx_t *ctx);

escpos_res_t fend_fill(fend_ctx_t *ctx, const void *buff, escpos_u32_t size);

escpos_res_t fend_proc(fend_ctx_t *ctx);

#endif
