#include "../clock.h"

int clock_negative_query_quantity(void)
{
    int ret;
    struct sbi_rpxy_ctx rpxy_ctx;
    struct rpmi_get_num_clocks_rx rx;
    rpxy_ctx.tpid = expected_clock_tpid + 1;
    ret = val_send_normal_message(rpxy_ctx.tpid,
                                RPMI_SRVGRP_CLOCK,
                                RPMI_CLK_SRV_GET_SYSTEM_CLOCKS,
                                0, 0, &rx, 0);

    val_print(VAL_VERBOSE_DEBUG, "Expected return = SBI_ERR_NOT_SUPPORTED (%d)\n", SBI_ERR_NOT_SUPPORTED);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return   =", ret);

    if (ret == SBI_ERR_NOT_SUPPORTED) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
