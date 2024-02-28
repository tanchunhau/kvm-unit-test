#include "../system_suspend.h"

int system_suspend_neg_s2ram(void)
{
    int ret;

    struct sbiret sret;

    //sret = sbi_ecall(SBI_EXT_SUSP, SBI_EXT_SUSP_SYSTEM_SUSPEND, SBI_SUSP_SLEEP_TYPE_SUSPEND_TO_RAM, 0, 0, 0, 0, 0);

    sret = sbi_ecall(SBI_EXT_SUSP, SBI_EXT_SUSP_SYSTEM_SUSPEND, SBI_SUSP_SLEEP_TYPE_INVALID, 0, 0, 0, 0, 0);

    val_print(VAL_VERBOSE_DEBUG, "Expected sret.error = SBI_ERR_INVALID_PARAM (%d)\n", SBI_ERR_INVALID_PARAM);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return = ", sret.error);

    if (sret.error == SBI_ERR_INVALID_PARAM) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
