#include "../clock.h"

int clock_negative_query_supported_rates(void)
{
    int ret;
    struct sbi_rpxy_ctx rpxy_ctx;
    struct rpmi_get_supp_rates_tx tx;
    struct rpmi_get_supp_rates_rx rx;
    unsigned long rxmsg_len;
    rpxy_ctx.tpid = expected_clock_tpid;

    tx.clkid = expected_clock_nums;
    tx.clk_rate_idx = 0;
    ret = val_send_normal_message(rpxy_ctx.tpid,
                                RPMI_SRVGRP_CLOCK,
                                RPMI_CLK_SRV_GET_SUPPORTED_RATES,
                                &tx, sizeof(struct rpmi_get_supp_rates_tx),
                                &rx, &rxmsg_len);

    val_print(VAL_VERBOSE_DEBUG, "Expected rx.status = RPMI_ERROR_NOT_FOUND (%d)\n", RPMI_ERROR_NOT_FOUND);
    rpmi_status_map(VAL_VERBOSE_DEBUG, "Actual return   =", rx.status);

    val_print(VAL_VERBOSE_DEBUG, "Expected return = SBI_SUCCESS (%d)\n", SBI_SUCCESS);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return   =", ret);

    if (ret == SBI_SUCCESS && rx.status == RPMI_ERROR_NOT_FOUND) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
