#include "../cppc.h"

void test_cppc(void)
{
    int num_pass = 0;
    int num_skip = 0;
    int num_fail = 0;

    if (!has_cppc_ext) {
        val_print(VAL_VERBOSE_INFO, "\n...Skip CPPC tests\n");
        return;
    }

    val_print(VAL_VERBOSE_INFO, "\n\t\t*** Starting CPPC tests ***\n");

    val_print(VAL_VERBOSE_INFO, "500 : cppc_probe_ext\n");
    if (cppc_probe_ext() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n501 : cppc_read\n");
    if (cppc_read() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n502 : cppc_write\n");
    if (cppc_write() == VAL_SUCCESS) {
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
