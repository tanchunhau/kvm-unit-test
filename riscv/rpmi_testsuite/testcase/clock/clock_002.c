#include "../clock.h"

int clock_query_quantity(void)
{
    int ret;

    struct sbi_rpxy_ctx rpxy_ctx;
    struct rpmi_get_num_clocks_rx rx;
    rpxy_ctx.tpid = expected_clock_tpid;
    ret = val_send_normal_message(rpxy_ctx.tpid,
                                RPMI_SRVGRP_CLOCK,
                                RPMI_CLK_SRV_GET_SYSTEM_CLOCKS,
                                0, 0, &rx, 0);

    sbi_error_map(VAL_VERBOSE_DEBUG, "send_normal_message return", ret);
    rpmi_status_map(VAL_VERBOSE_DEBUG, "rx.status return", rx.status);

    val_print(VAL_VERBOSE_DEBUG, "Expected num_clocks = %d\n", expected_clock_nums);
    val_print(VAL_VERBOSE_DEBUG, "  Readed num_clocks = %d\n", rx.num_clocks);

    if (ret == SBI_SUCCESS && rx.status == RPMI_SUCCESS) {
        if (rx.num_clocks == expected_clock_nums) {
            ret = VAL_SUCCESS;
        } else {
            ret = VAL_ERROR;
        }
    }
    else {
        ret = VAL_ERROR;
    }

    return ret;
}