#include "../clock.h"

int clock_query_supported_rates(u32 clkid, struct sbi_rpxy_clk *rpxy_clk)
{
    val_print(VAL_VERBOSE_DEBUG, "rpxy_clk->id = %u\n", rpxy_clk->id);
    int ret, rateidx, j = 0;
    size_t clk_rate_idx = 0;
    int index = 0;
    bool is_matches_expected = true;
    struct sbi_rpxy_ctx rpxy_ctx;
    struct rpmi_get_supp_rates_tx tx;
    struct rpmi_get_supp_rates_rx rx;
    unsigned long rxmsg_len;
    rpxy_ctx.tpid = expected_clock_tpid;

    tx.clkid = clkid;
    tx.clk_rate_idx = 0;
    ret = val_send_normal_message(rpxy_ctx.tpid,
                                RPMI_SRVGRP_CLOCK,
                                RPMI_CLK_SRV_GET_SUPPORTED_RATES,
                                &tx, sizeof(struct rpmi_get_supp_rates_tx),
                                &rx, &rxmsg_len);

    val_print(VAL_VERBOSE_DEBUG, "rx.status = %d\n", rx.status);

    sbi_error_map(VAL_VERBOSE_DEBUG, "send_normal_message return", ret);
    rpmi_status_map(VAL_VERBOSE_DEBUG, "rx.status return", rx.status);

    val_print(VAL_VERBOSE_DEBUG, "send_normal_message rx.status = %ld\n", (long)rx.status);

    if (rpxy_clk->type == SBI_RPXY_CLK_DISCRETE) {
        for (rateidx = 0; rateidx < rx.returned; rateidx++) {
            rpxy_clk->rates->discrete[rateidx] =
                GET_RATE_U64(rx.rates.discrete[rateidx].hi,
                         rx.rates.discrete[rateidx].lo);

            val_print(VAL_VERBOSE_DEBUG, "Expected rates (discrete) [%d] = %lu\n", index, get_expected_clock_attributes(rpxy_clk->id)->rates->discrete[index]);
            val_print(VAL_VERBOSE_DEBUG, "  Actual rates (discrete) [%d] = %lu\n", rateidx, rpxy_clk->rates->discrete[rateidx]);

            if (rpxy_clk->rates->discrete[rateidx] != get_expected_clock_attributes(rpxy_clk->id)->rates->discrete[index]) {
                is_matches_expected = false;
            }

            index++;
        }

        while (rx.remaining) {
            clk_rate_idx += rx.returned;
            tx.clk_rate_idx = clk_rate_idx;
            ret = val_send_normal_message(rpxy_ctx.tpid,
                    RPMI_SRVGRP_CLOCK,
                    RPMI_CLK_SRV_GET_SUPPORTED_RATES,
                    &tx, sizeof(struct rpmi_get_supp_rates_tx),
                    &rx, &rxmsg_len);
            for (j = 0; rateidx < (clk_rate_idx+rx.returned) &&
                        j < rx.returned; rateidx++, j++) {
                rpxy_clk->rates->discrete[rateidx] =
                    GET_RATE_U64(rx.rates.discrete[j].hi,
                         rx.rates.discrete[j].lo);

                val_print(VAL_VERBOSE_DEBUG, "Expected rates (discrete) [%d] = %lu\n", index, get_expected_clock_attributes(rpxy_clk->id)->rates->discrete[index]);
                val_print(VAL_VERBOSE_DEBUG, "  Actual rates (discrete) [%d] = %lu\n", rateidx, rpxy_clk->rates->discrete[rateidx]);

                if (rpxy_clk->rates->discrete[rateidx] != get_expected_clock_attributes(rpxy_clk->id)->rates->discrete[index]) {
                    is_matches_expected = false;
                }

                index++;
            }
        }
    } else if (rpxy_clk->type == SBI_RPXY_CLK_LINEAR) {
        rpxy_clk->rates->linear.min =
                GET_RATE_U64(rx.rates.linear.min_hi,
                         rx.rates.linear.min_lo);
        rpxy_clk->rates->linear.max =
                GET_RATE_U64(rx.rates.linear.max_hi,
                         rx.rates.linear.max_lo);
        rpxy_clk->rates->linear.step =
                GET_RATE_U64(rx.rates.linear.step_hi,
                         rx.rates.linear.step_lo);

        val_print(VAL_VERBOSE_DEBUG, "Expected rates (linear) min = %lu\n", get_expected_clock_attributes(rpxy_clk->id)->rates->linear.min);
        val_print(VAL_VERBOSE_DEBUG, "  Actual rates (linear) min = %lu\n", rpxy_clk->rates->linear.min);

        val_print(VAL_VERBOSE_DEBUG, "Expected rates (linear) max = %lu\n", get_expected_clock_attributes(rpxy_clk->id)->rates->linear.max);
        val_print(VAL_VERBOSE_DEBUG, "  Actual rates (linear) max = %lu\n", rpxy_clk->rates->linear.max);

        val_print(VAL_VERBOSE_DEBUG, "Expected rates (linear) step = %lu\n", get_expected_clock_attributes(rpxy_clk->id)->rates->linear.step);
        val_print(VAL_VERBOSE_DEBUG, "  Actual rates (linear) step = %lu\n", rpxy_clk->rates->linear.step);

        if (get_expected_clock_attributes(rpxy_clk->id)->rates->linear.min != rpxy_clk->rates->linear.min
            || get_expected_clock_attributes(rpxy_clk->id)->rates->linear.max != rpxy_clk->rates->linear.max
            || get_expected_clock_attributes(rpxy_clk->id)->rates->linear.step != rpxy_clk->rates->linear.step
           ) {
            is_matches_expected = false;
        }
    }

    if (ret == SBI_SUCCESS && rx.status == RPMI_SUCCESS && is_matches_expected) {
        ret = VAL_SUCCESS;
    }
    else {
        ret = VAL_ERROR;
    }

    return ret;
}
