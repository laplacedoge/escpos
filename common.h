#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

typedef int8_t      escpos_s8_t;
typedef uint8_t     escpos_u8_t;
typedef int16_t     escpos_s16_t;
typedef uint16_t    escpos_u16_t;
typedef int32_t     escpos_s32_t;
typedef uint32_t    escpos_u32_t;
typedef int64_t     escpos_s64_t;
typedef uint64_t    escpos_u64_t;

typedef enum escpos_res {
    ESCPOS_OK               = 0,
    ESCPOS_ERR              = -1,
    ESCPOS_ERR_NO_MEM       = -2,
    ESCPOS_ERR_BAD_CONF     = -3,
    ESCPOS_ERR_NO_SPA       = -4,
    ESCPOS_ERR_NO_DAT       = -5,
    ESCPOS_ERR_TIMEOUT      = -6,
    ESCPOS_ERR_BAD_CMD      = -7,
    ESCPOS_ERR_BAD_SUB      = -8,
} escpos_res_t;

typedef escpos_res_t (* bend_cmd_cb_ESC_at_t)(void);
typedef escpos_res_t (* bend_cmd_cb_FF_t)(void);
typedef escpos_res_t (* bend_cmd_cb_SO_t)(void);
typedef escpos_res_t (* bend_cmd_cb_LF_t)(void);
typedef escpos_res_t (* bend_cmd_cb_CR_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_J_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_d_t)(void);
typedef escpos_res_t (* bend_cmd_cb_HT_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_FF_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_H99_t)(void);

typedef escpos_res_t (* bend_cmd_cb_ESC_exclamation_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_exclamation_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_M_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_minus_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_E_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_B_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_V_t)(void);

typedef escpos_res_t (* bend_cmd_cb_ESC_dollar_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_D_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_2_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_3_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_SP_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_a_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_L_t)(void);

typedef escpos_res_t (* bend_cmd_cb_ESC_asterisk_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_asterisk_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_forwardslash_t)(void);
typedef escpos_res_t (* bend_cmd_cb_FS_P_t)(void);

typedef escpos_res_t (* bend_cmd_cb_GS_h_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_w_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_H_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_f_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_k_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_Z_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_Z_t)(void);

typedef escpos_res_t (* bend_cmd_cb_GS_singlequote_t)(void);
typedef escpos_res_t (* bend_cmd_cb_GS_doublequote_t)(void);

typedef escpos_res_t (* bend_cmd_cb_FS_ampersand_t)(void);
typedef escpos_res_t (* bend_cmd_cb_FS_dot_t)(void);
typedef escpos_res_t (* bend_cmd_cb_FS_U_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_t_t)(void);
typedef escpos_res_t (* bend_cmd_cb_ESC_R_t)(void);
typedef escpos_res_t (* bend_cmd_cb_US_f_t)(void);
typedef escpos_res_t (* bend_cmd_cb_US_q_t)(void);

typedef escpos_res_t (* bend_cmd_cb_US_sBrPH1FH73H42H72H50_t)(void);
typedef escpos_res_t (* bend_cmd_cb_US_sBrP_t)(void);


// typedef escpos_res_t (* escpos_ESC_at_cb_t)(void);

// typedef escpos_res_t (* escpos_ESC_at_cb_t)(void);
// typedef escpos_res_t (* escpos_FF_cb_t)(void);
// typedef escpos_res_t (* escpos_SO_cb_t)(void);
// typedef escpos_res_t (* escpos_LF_cb_t)(void);
// typedef escpos_res_t (* escpos_CR_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_J_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_d_cb_t)(void);
// typedef escpos_res_t (* escpos_HT_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_FF_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_H99_cb_t)(void);

// typedef escpos_res_t (* escpos_ESC_exclamation_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_exclamation_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_M_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_minus_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_E_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_B_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_V_cb_t)(void);

// typedef escpos_res_t (* escpos_ESC_dollar_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_D_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_2_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_3_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_SP_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_a_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_L_cb_t)(void);

// typedef escpos_res_t (* escpos_ESC_asterisk_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_asterisk_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_forwardslash_cb_t)(void);
// typedef escpos_res_t (* escpos_FS_P_cb_t)(void);

// typedef escpos_res_t (* escpos_GS_h_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_w_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_H_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_f_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_k_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_Z_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_Z_cb_t)(void);

// typedef escpos_res_t (* escpos_GS_singlequote_cb_t)(void);
// typedef escpos_res_t (* escpos_GS_doublequote_cb_t)(void);

// typedef escpos_res_t (* escpos_FS_ampersand_cb_t)(void);
// typedef escpos_res_t (* escpos_FS_dot_cb_t)(void);
// typedef escpos_res_t (* escpos_FS_U_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_t_cb_t)(void);
// typedef escpos_res_t (* escpos_ESC_R_cb_t)(void);
// typedef escpos_res_t (* escpos_US_f_cb_t)(void);
// typedef escpos_res_t (* escpos_US_q_cb_t)(void);

// typedef escpos_res_t (* escpos_US_sBrPH1FH73H42H72H50_cb_t)(void);
// typedef escpos_res_t (* escpos_US_sBrP_cb_t)(void);

typedef struct escpos_cmd_cb_tab {

    bend_cmd_cb_ESC_at_t cmd_cb_ESC_at;
    bend_cmd_cb_FF_t cmd_cb_FF;
    bend_cmd_cb_SO_t cmd_cb_SO;
    bend_cmd_cb_LF_t cmd_cb_LF;
    bend_cmd_cb_CR_t cmd_cb_CR;
    bend_cmd_cb_ESC_J_t cmd_cb_ESC_J;
    bend_cmd_cb_ESC_d_t cmd_cb_ESC_d;
    bend_cmd_cb_HT_t cmd_cb_HT;
    bend_cmd_cb_GS_FF_t cmd_cb_GS_FF;
    bend_cmd_cb_GS_H99_t cmd_cb_GS_H99;

    bend_cmd_cb_ESC_exclamation_t cmd_cb_ESC_exclamation;
    bend_cmd_cb_GS_exclamation_t cmd_cb_GS_exclamation;
    bend_cmd_cb_ESC_M_t cmd_cb_ESC_M;
    bend_cmd_cb_ESC_minus_t cmd_cb_ESC_minus;
    bend_cmd_cb_ESC_E_t cmd_cb_ESC_E;
    bend_cmd_cb_GS_B_t cmd_cb_GS_B;
    bend_cmd_cb_ESC_V_t cmd_cb_ESC_V;

    bend_cmd_cb_ESC_dollar_t cmd_cb_ESC_dollar;
    bend_cmd_cb_ESC_D_t cmd_cb_ESC_D;
    bend_cmd_cb_ESC_2_t cmd_cb_ESC_2;
    bend_cmd_cb_ESC_3_t cmd_cb_ESC_3;
    bend_cmd_cb_ESC_SP_t cmd_cb_ESC_SP;
    bend_cmd_cb_ESC_a_t cmd_cb_ESC_a;
    bend_cmd_cb_GS_L_t cmd_cb_GS_L;

    bend_cmd_cb_ESC_asterisk_t cmd_cb_ESC_asterisk;
    bend_cmd_cb_GS_asterisk_t cmd_cb_GS_asterisk;
    bend_cmd_cb_GS_forwardslash_t cmd_cb_GS_forwardslash;
    bend_cmd_cb_FS_P_t cmd_cb_FS_P;

    bend_cmd_cb_GS_h_t cmd_cb_GS_h;
    bend_cmd_cb_GS_w_t cmd_cb_GS_w;
    bend_cmd_cb_GS_H_t cmd_cb_GS_H;
    bend_cmd_cb_GS_f_t cmd_cb_GS_f;
    bend_cmd_cb_GS_k_t cmd_cb_GS_k;
    bend_cmd_cb_GS_Z_t cmd_cb_GS_Z;
    bend_cmd_cb_ESC_Z_t cmd_cb_ESC_Z;

    bend_cmd_cb_GS_singlequote_t cmd_cb_GS_singlequote;
    bend_cmd_cb_GS_doublequote_t cmd_cb_GS_doublequote;

    bend_cmd_cb_FS_ampersand_t cmd_cb_FS_ampersand;
    bend_cmd_cb_FS_dot_t cmd_cb_FS_dot;
    bend_cmd_cb_FS_U_t cmd_cb_FS_U;
    bend_cmd_cb_ESC_t_t cmd_cb_ESC_t;
    bend_cmd_cb_ESC_R_t cmd_cb_ESC_R;
    bend_cmd_cb_US_f_t cmd_cb_US_f;
    bend_cmd_cb_US_q_t cmd_cb_US_q;

    bend_cmd_cb_US_sBrPH1FH73H42H72H50_t cmd_cb_US_sBrPH1FH73H42H72H50;
    bend_cmd_cb_US_sBrP_t cmd_cb_US_sBrP;


    // escpos_ESC_at_cb_t ESC_at_cb;
    // escpos_FF_cb_t FF_cb;
    // escpos_SO_cb_t SO_cb;
    // escpos_LF_cb_t LF_cb;
    // escpos_CR_cb_t CR_cb;
    // escpos_ESC_J_cb_t ESC_J_cb;
    // escpos_ESC_d_cb_t ESC_d_cb;
    // escpos_HT_cb_t HT_cb;
    // escpos_GS_FF_cb_t GS_FF_cb;
    // escpos_GS_H99_cb_t GS_H99_cb;

    // escpos_ESC_exclamation_cb_t ESC_exclamation_cb;
    // escpos_GS_exclamation_cb_t GS_exclamation_cb;
    // escpos_ESC_M_cb_t ESC_M_cb;
    // escpos_ESC_minus_cb_t ESC_minus_cb;
    // escpos_ESC_E_cb_t ESC_E_cb;
    // escpos_GS_B_cb_t GS_B_cb;
    // escpos_ESC_V_cb_t ESC_V_cb;

    // escpos_ESC_dollar_cb_t ESC_dollar_cb;
    // escpos_ESC_D_cb_t ESC_D_cb;
    // escpos_ESC_2_cb_t ESC_2_cb;
    // escpos_ESC_3_cb_t ESC_3_cb;
    // escpos_ESC_SP_cb_t ESC_SP_cb;
    // escpos_ESC_a_cb_t ESC_a_cb;
    // escpos_GS_L_cb_t GS_L_cb;

    // escpos_ESC_asterisk_cb_t ESC_asterisk_cb;
    // escpos_GS_asterisk_cb_t GS_asterisk_cb;
    // escpos_GS_forwardslash_cb_t GS_forwardslash_cb;
    // escpos_FS_P_cb_t FS_P_cb;

    // escpos_GS_h_cb_t GS_h_cb;
    // escpos_GS_w_cb_t GS_w_cb;
    // escpos_GS_H_cb_t GS_H_cb;
    // escpos_GS_f_cb_t GS_f_cb;
    // escpos_GS_k_cb_t GS_k_cb;
    // escpos_GS_Z_cb_t GS_Z_cb;
    // escpos_ESC_Z_cb_t ESC_Z_cb;

    // escpos_GS_singlequote_cb_t GS_singlequote_cb;
    // escpos_GS_doublequote_cb_t GS_doublequote_cb;

    // escpos_FS_ampersand_cb_t FS_ampersand_cb;
    // escpos_FS_dot_cb_t FS_dot_cb;
    // escpos_FS_U_cb_t FS_U_cb;
    // escpos_ESC_t_cb_t ESC_t_cb;
    // escpos_ESC_R_cb_t ESC_R_cb;
    // escpos_US_f_cb_t US_f_cb;
    // escpos_US_q_cb_t US_q_cb;

    // escpos_US_sBrPH1FH73H42H72H50_cb_t US_sBrPH1FH73H42H72H50_cb;
    // escpos_US_sBrP_cb_t US_sBrP_cb;
} escpos_cmd_cb_tab_t;

#endif
