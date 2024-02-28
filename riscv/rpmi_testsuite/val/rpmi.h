#ifndef _RPMI_H
#define _RPMI_H

#include <stdlib.h>

#define SBI_EXT_BASE            0x10
#define RPMI_SRVGRP_CLOCK       0x00007
#define SBI_EXT_RPXY            0x52505859

/* SBI return error codes */
#define SBI_SUCCESS                 0
#define SBI_ERR_FAILURE             -1
#define SBI_ERR_NOT_SUPPORTED       -2
#define SBI_ERR_INVALID_PARAM       -3
#define SBI_ERR_DENIED              -4
#define SBI_ERR_INVALID_ADDRESS     -5
#define SBI_ERR_ALREADY_AVAILABLE   -6
#define SBI_ERR_ALREADY_STARTED     -7
#define SBI_ERR_ALREADY_STOPPED     -8
#define SBI_ERR_INVALID_STATE       -10
#define SBI_ERR_BAD_RANGE           -11
#define SBI_ERR_BUSY                -12

enum rpmi_clock_service_id {
    RPMI_CLK_SRV_ENABLE_NOTIFICATION = 0x01,
    RPMI_CLK_SRV_GET_SYSTEM_CLOCKS = 0x02,
    RPMI_CLK_SRV_GET_ATTRIBUTES = 0x03,
    RPMI_CLK_SRV_GET_SUPPORTED_RATES = 0x04,
    RPMI_CLK_SRV_SET_CONFIG = 0x05,
    RPMI_CLK_SRV_GET_CONFIG = 0x06,
    RPMI_CLK_SRV_SET_RATE = 0x07,
    RPMI_CLK_SRV_GET_RATE = 0x08,
    RPMI_CLK_SRV_ID_MAX_COUNT,
};

enum sbi_ext_rpxy_fid {
    SBI_EXT_RPXY_PROBE = 0,
    SBI_EXT_RPXY_SETUP_SHMEM,
    SBI_EXT_RPXY_SEND_NORMAL_MSG,
    SBI_EXT_RPXY_SEND_POSTED_MSG,
    SBI_EXT_RPXY_GET_NOTIFICATIONS,
};

enum rpmi_status_code {
    RPMI_SUCCESS = 0,
    RPMI_ERROR_FAILED = -1,
    RPMI_ERROR_NOT_SUPPORTED = -2,
    RPMI_ERROR_INVALID_PARAMETER = -3,
    RPMI_ERROR_DENIED = -4,
    RPMI_ERROR_NOT_FOUND = -5,
    RPMI_ERROR_OUT_OF_RANGE = -6,
    RPMI_ERROR_OUT_OF_RESOURCE = -7,
    RPMI_ERROR_HW_FAULT = -8,
    RPMI_ERROR_BUSY = -9,
    RPMI_ERROR_TIMEOUT = -10,
    RPMI_ERROR_COMMS = -11,
    RPMI_ERROR_ALREADY = -12,
    RPMI_ERROR_EXTENSION = 13,
};

struct sbi_rpxy {
    void *shmem;
    //void *shmem_phys;
    unsigned long long shmem_phys;
    bool active;
};

// clock
#define SBI_RPXY_CLK_MAX_NUM_RATES    16
#define SBI_RPXY_CLK_NAME_LEN        16
#define GET_RATE_LO_U32(rate_u64)    ((u32)rate_u64)
#define GET_RATE_HI_U32(rate_u64)    ((u32)(rate_u64 >> 32))
#define GET_RATE_U64(hi_u32, lo_u32)    ((u64)hi_u32 << 32 | lo_u32)

struct rpmi_get_attrs_tx {
    u32 clkid;
};

struct rpmi_get_attrs_rx {
    s32 status;
    u32 flags;
    u32 num_rates;
    u32 transition_latency;
    char name[SBI_RPXY_CLK_NAME_LEN];
};

enum sbi_rpxy_clk_type {
    SBI_RPXY_CLK_DISCRETE = 0,
    SBI_RPXY_CLK_LINEAR = 1,
    SBI_RPXY_CLK_TYPE_MAX_IDX,
};

struct sbi_rpxy_ctx {
    /* transport id */
    unsigned long tpid;
    unsigned long max_msg_len;
};

struct rpmi_get_num_clocks_rx {
    s32 status;
    u32 num_clocks;
};

union sbi_rpxy_clk_rates {
    u64 discrete[SBI_RPXY_CLK_MAX_NUM_RATES];
    struct {
        u64 min;
        u64 max;
        u64 step;
    } linear;
};

union rpmi_clk_rate {
    struct {
        u32 lo;
        u32 hi;
    } discrete[SBI_RPXY_CLK_MAX_NUM_RATES];
    struct {
        u32 min_lo;
        u32 min_hi;
        u32 max_lo;
        u32 max_hi;
        u32 step_lo;
        u32 step_hi;
    } linear;
};

struct rpmi_get_supp_rates_tx {
    u32 clkid;
    u32 clk_rate_idx;
};

struct rpmi_get_supp_rates_rx {
    u32 status;
    u32 flags;
    u32 remaining;
    u32 returned;
    union rpmi_clk_rate rates;
};

struct sbi_rpxy_clk {
    u32 id;
    u32 num_rates;
    u32 transition_latency;
    enum sbi_rpxy_clk_type type;
    union sbi_rpxy_clk_rates *rates;
    char name[SBI_RPXY_CLK_NAME_LEN];
    //struct clk_hw hw;
};

#endif /* _RPMI_H */
