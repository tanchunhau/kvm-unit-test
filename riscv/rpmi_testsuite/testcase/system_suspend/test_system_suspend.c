#include "../system_suspend.h"

void test_system_suspend(void)
{
    int num_pass = 0;
    int num_skip = 0;
    int num_fail = 0;

    val_print(VAL_VERBOSE_INFO, "\n\t\t*** Starting system suspend tests ***\n");

    val_print(VAL_VERBOSE_INFO, "400 : system_suspend_probe_ext\n");
    if (system_suspend_probe_ext() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n401 : system_suspend_neg_s2ram\n");

    if (system_suspend_neg_s2ram() == VAL_SUCCESS) {
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
