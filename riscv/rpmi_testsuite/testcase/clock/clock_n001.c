#include "../clock.h"

int clock_negative_srvgrp_probe(void)
{
    struct sbi_rpxy_ctx rpxy_ctx;
    unsigned long max_msg_len = 15;
    rpxy_ctx.tpid = expected_clock_tpid + 1;
    int ret;
    ret = val_srvgrp_probe(rpxy_ctx.tpid, RPMI_SRVGRP_CLOCK, &max_msg_len);

    val_print(VAL_VERBOSE_DEBUG, "Expected return = SBI_ERR_NOT_SUPPORTED (%d)\n", SBI_ERR_NOT_SUPPORTED);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return   =", ret);

    if (ret == SBI_ERR_NOT_SUPPORTED) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
