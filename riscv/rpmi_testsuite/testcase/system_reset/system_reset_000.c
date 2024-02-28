#include "../system_reset.h"

int system_reset_probe_ext(void)
{
    struct sbiret sret;

    sret = sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_PROBE_EXT, SBI_EXT_SRST,
            0, 0, 0, 0, 0);

    sbi_error_map(VAL_VERBOSE_DEBUG, "SBI_EXT_SRST probe return", sret.error);
    val_print(VAL_VERBOSE_DEBUG, "Expected sret.value = 1\n");
    val_print(VAL_VERBOSE_DEBUG, "Actual sret.value = %ld\n", sret.value);

    if (!sret.error && sret.value == 1) {
        return VAL_SUCCESS;
    }

    return VAL_ERROR;
}
