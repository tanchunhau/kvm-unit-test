#include "../clock.h"

int clock_srvgrp_probe(void)
{
    struct sbi_rpxy_ctx rpxy_ctx;
    unsigned long max_msg_len = 15;
    rpxy_ctx.tpid = expected_clock_tpid;
    int ret;
    ret = val_srvgrp_probe(rpxy_ctx.tpid, RPMI_SRVGRP_CLOCK, &max_msg_len);
    ret = sbi_error_map(VAL_VERBOSE_DEBUG, "service group probe return", ret);

    val_print(VAL_VERBOSE_DEBUG, "rvgrp_probe max_msg_len = %ld\n", max_msg_len);

    if (!max_msg_len) {
        ret = VAL_ERROR;
    }

    return ret;
}