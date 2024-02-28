#include "../system_reset.h"

int system_reset_neg_warm_reboot(void)
{
    int ret;

    struct sbiret sret;

    sret = sbi_ecall(SBI_EXT_SRST, SBI_EXT_SRST_RESET, SBI_SRST_RESET_TYPE_WARM_REBOOT, SBI_SRST_RESET_REASON_INVALID,
          0, 0, 0, 0);

    val_print(VAL_VERBOSE_DEBUG, "Expected sret.error = SBI_ERR_INVALID_PARAM (%d)\n", SBI_ERR_INVALID_PARAM);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return = ", sret.error);

    if (sret.error == SBI_ERR_INVALID_PARAM) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
