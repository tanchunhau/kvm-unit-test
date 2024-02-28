#include "../hsm.h"

int hsm_negative_hart_start(void)
{
    int ret;

    struct sbiret sret;

    unsigned long started_hart_id = expected_hsm_nums;

    val_print(VAL_VERBOSE_DEBUG, "negative hsm_hart_start (%lu) ", started_hart_id);

    sret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_START,
            started_hart_id, 0, 0, 0, 0, 0);

    val_print(VAL_VERBOSE_DEBUG, "Expected sret.error = SBI_ERR_INVALID_PARAM (%d)\n", SBI_ERR_INVALID_PARAM);
    sbi_error_map(VAL_VERBOSE_DEBUG, "Actual return = ", sret.error);

    if (sret.error == SBI_ERR_INVALID_PARAM) {
        ret = VAL_SUCCESS;
    } else {
        ret = VAL_ERROR;
    }

    return ret;
}
