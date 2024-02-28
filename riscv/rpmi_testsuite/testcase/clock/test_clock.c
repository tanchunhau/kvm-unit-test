#include "../clock.h"

void test_clock(void)
{
    int num_pass = 0;
    int num_skip = 0;
    int num_fail = 0;

    if (!has_clock_srvgrp) {
        val_print(VAL_VERBOSE_INFO, "\n...Skip CLOCK tests\n");
        return;
    }
    val_print(VAL_VERBOSE_INFO, "\n\t\t*** Starting CLOCK tests ***\n");
    val_print(VAL_VERBOSE_INFO, "101 : service group probe\n");
    if (clock_srvgrp_probe() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n102 : get num_clocks\n");
    if (clock_query_quantity() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    struct sbi_rpxy_clk rpxy_clk[expected_clock_nums];
    u32 clkid = 0;
    bool is_test_pass = 1;

    val_print(VAL_VERBOSE_INFO, "\n103 : clock_query_attributes\n");

    for (clkid = 0; clkid < expected_clock_nums; clkid++) {
        if (clock_query_attrs(clkid, &rpxy_clk[clkid]) == VAL_SUCCESS) {
            val_print(VAL_VERBOSE_INFO, "Sub test result\t: PASS\n\n");
        } else {
            val_print(VAL_VERBOSE_INFO, "Sub test result\t: FAIL\n\n");
            is_test_pass = 0;
        }
    }

    if (is_test_pass == 1) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    }
    else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    is_test_pass = 1;
    val_print(VAL_VERBOSE_INFO, "\n104 : clock_query_supported_rates\n");
    for (clkid = 0; clkid < expected_clock_nums; clkid++) {
        if (clock_query_supported_rates(clkid, &rpxy_clk[clkid]) == VAL_SUCCESS) {
            val_print(VAL_VERBOSE_INFO, "Sub test result\t: PASS\n\n");
        } else {
            val_print(VAL_VERBOSE_INFO, "Sub test result\t: FAIL\n\n");
            is_test_pass = 0;
        }
    }

    if (is_test_pass == 1) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    }
    else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n105 : (Negative) service group probe with wrong transport id\n");
    if (clock_negative_srvgrp_probe() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n106 : (Negative) get num_clocks with wrong transport id\n");
    if (VAL_SUCCESS == clock_negative_query_quantity()) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n107 : (Negative) get clock attribute with wrong clock id\n");
    if (VAL_SUCCESS == clock_negative_query_attrs()) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n108 : (Negative) get clock supported rates with wrong clock id\n");
    if (VAL_SUCCESS == clock_negative_query_supported_rates()) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n109 : (Negative) get clock supported rates with wrong clock rate index\n");
    if (VAL_SUCCESS == clock_negative_query_supported_rates_wrong_rate_index()) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "************************************************************************\n");
    val_print(VAL_VERBOSE_INFO, "  TOTAL TESTS: %d\tPASSED: %d\tFAILED: %d\tSKIPPED: %d\n",
                        (num_pass + num_fail + num_skip), num_pass, num_fail, num_skip);
    val_print(VAL_VERBOSE_INFO, "************************************************************************\n");
}
