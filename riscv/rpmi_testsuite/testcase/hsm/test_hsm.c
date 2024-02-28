#include "../hsm.h"

void test_hsm(void)
{
    int num_pass = 0;
    int num_skip = 0;
    int num_fail = 0;


    if (!has_hsm_ext) {
        val_print(VAL_VERBOSE_INFO, "\n...Skip HSM tests\n");
        return;
    }

    val_print(VAL_VERBOSE_INFO, "\n\t\t*** Starting HSM tests ***\n");

    val_print(VAL_VERBOSE_INFO, "200 : hsm_probe_ext\n");
    if (hsm_probe_ext() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n201 : hsm_hart_get_status\n");

    unsigned long started_hart_id = 0;

    if (hsm_hart_get_status(&started_hart_id) == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    val_print(VAL_VERBOSE_INFO, "\n202 : hsm_hart_start\n");
    if (hsm_hart_start(&started_hart_id) == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }

    //---- this will cause shutdown ---
    /*
    val_print(VAL_VERBOSE_INFO, "\n203 : hsm_hart_stop\n");
    if (hsm_hart_stop(&started_hart_id) == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
        num_pass++;
    } else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
        num_fail++;
    }
    */

    val_print(VAL_VERBOSE_INFO, "\n204 : hsm_negative_hart_start\n");
    if (hsm_negative_hart_start() == VAL_SUCCESS) {
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
