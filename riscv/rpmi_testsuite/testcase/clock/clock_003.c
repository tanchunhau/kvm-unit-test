#include "../clock.h"

int clock_query_attrs(u32 clkid, struct sbi_rpxy_clk *rpxy_clk)
{
    int ret;
    struct sbi_rpxy_ctx rpxy_ctx;

    u8 format;
    unsigned long rxmsg_len;
    struct rpmi_get_attrs_tx tx;
    struct rpmi_get_attrs_rx rx;

    tx.clkid = clkid;
    rpxy_ctx.tpid = expected_clock_tpid;
    ret = val_send_normal_message(rpxy_ctx.tpid,
                    RPMI_SRVGRP_CLOCK,
                    RPMI_CLK_SRV_GET_ATTRIBUTES,
                    &tx, sizeof(struct rpmi_get_attrs_tx),
                    &rx, &rxmsg_len);

    ret = sbi_error_map(VAL_VERBOSE_DEBUG, "send_normal_message return", ret);
    rpmi_status_map(VAL_VERBOSE_DEBUG, "rx.status return", rx.status);

    rpxy_clk->id = clkid;
    rpxy_clk->num_rates = rx.num_rates;
    rpxy_clk->transition_latency = rx.transition_latency;
    memcpy(rpxy_clk->name, rx.name, SBI_RPXY_CLK_NAME_LEN);

    val_print(VAL_VERBOSE_DEBUG, "id = %u\n", rpxy_clk->id);
    val_print(VAL_VERBOSE_DEBUG, "Expected num_rates = %u\n", get_expected_clock_attributes(rpxy_clk->id)->num_rates);
    val_print(VAL_VERBOSE_DEBUG, "  Actual num_rates = %u\n", rpxy_clk->num_rates);
    val_print(VAL_VERBOSE_DEBUG, "Expected transition_latency  = %u\n", get_expected_clock_attributes(rpxy_clk->id)->transition_latency);
    val_print(VAL_VERBOSE_DEBUG, "  Actual transition_latency  = %u\n", rpxy_clk->transition_latency);
    val_print(VAL_VERBOSE_DEBUG, "Expected name = %s\n", get_expected_clock_attributes(rpxy_clk->id)->name);
    val_print(VAL_VERBOSE_DEBUG, "  Actual name = %s\n", rpxy_clk->name);

    switch (get_expected_clock_attributes(rpxy_clk->id)->type) {
        case SBI_RPXY_CLK_DISCRETE:
            val_print(VAL_VERBOSE_DEBUG, "Expected format = DISCRETE(%d)\n", SBI_RPXY_CLK_DISCRETE);
            break;
        case SBI_RPXY_CLK_LINEAR:
            val_print(VAL_VERBOSE_DEBUG, "Expected format = LINEAR(%d)\n", SBI_RPXY_CLK_LINEAR);
            break;
        default:
            val_print(VAL_VERBOSE_DEBUG, "Wrong Expected format(%d)\n", get_expected_clock_attributes(rpxy_clk->id)->type);
    }

    format = rx.flags >> 30;
    if (format >= SBI_RPXY_CLK_TYPE_MAX_IDX) {
        val_print(VAL_VERBOSE_DEBUG, "Error: format(%d) >= MAX_IDX(%d)\n", (int)format, (int)SBI_RPXY_CLK_TYPE_MAX_IDX);
        ret = VAL_ERROR;
    } else if (format == SBI_RPXY_CLK_DISCRETE) {
        val_print(VAL_VERBOSE_DEBUG, "  Actual format = DISCRETE(%d)\n", (int)format);
    } else if (format == SBI_RPXY_CLK_LINEAR) {
        val_print(VAL_VERBOSE_DEBUG, "  Actual format = LINEAR(%d)\n", (int)format);
    }

    rpxy_clk->type = format;

    if (ret == SBI_SUCCESS && rx.status == RPMI_SUCCESS) {
        if (get_expected_clock_attributes(rpxy_clk->id)->num_rates == rpxy_clk->num_rates
            && get_expected_clock_attributes(rpxy_clk->id)->transition_latency == rpxy_clk->transition_latency
            && strcmp(get_expected_clock_attributes(rpxy_clk->id)->name, rpxy_clk->name) == 0
            && get_expected_clock_attributes(rpxy_clk->id)->type == format
            ) {
            ret = VAL_SUCCESS;
        } else {
            ret = VAL_ERROR;
        }
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
