#include "../system_reset.h"

void test_system_reset(void)
{
    int num_pass = 0;
    int num_skip = 0;
    int num_fail = 0;

    val_print(VAL_VERBOSE_INFO, "\n\t\t*** Starting system reset tests ***\n");

    val_print(VAL_VERBOSE_INFO, "300 : system_reset_probe_ext\n");
    if (system_reset_probe_ext() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n301 : system_reset_neg_shutdown\n");

    if (system_reset_neg_shutdown() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n302 : system_reset_neg_cold_reboot\n");

    if (system_reset_neg_cold_reboot() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n303 : system_reset_neg_warm_reboot\n");

    if (system_reset_neg_warm_reboot() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n304 : system_reset_neg_reboot_type\n");

    if (system_reset_neg_reboot_type() == VAL_SUCCESS) {
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
