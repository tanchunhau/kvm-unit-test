#include "../../val/val_interface.h"
#include "../../testcase/clock.h"
#include "../../testcase/hsm.h"
#include "../../testcase/system_reset.h"
#include "../../testcase/system_suspend.h"
#include "../../testcase/cppc.h"

int main(void)
{
    val_print(VAL_VERBOSE_INFO, "RPMI Test Suite Version 0.0.1\n\n");

    val_print(VAL_VERBOSE_INFO, "\t\t*** Test Initialization ***\n");

    if (val_init() == VAL_SUCCESS) {
        val_print(VAL_VERBOSE_INFO, "Result\t: PASS\n");
    }
    else {
        val_print(VAL_VERBOSE_INFO, "Result\t: FAIL\n");
    }

    test_clock();
    test_hsm();
    test_system_reset();
    test_system_suspend();
    test_cppc();

    return 0;
}
