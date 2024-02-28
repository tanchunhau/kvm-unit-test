#include "../hsm.h"

int hsm_hart_start(unsigned long* started_hart_id)
{
    int ret;

    struct sbiret sret;

    if (*started_hart_id >= (expected_hsm_nums - 1)) {
        *started_hart_id = *started_hart_id - 1;
    } else {
        *started_hart_id = *started_hart_id + 1;
    }

    val_print(VAL_VERBOSE_DEBUG, "hsm_hart_start (%lu) ", *started_hart_id);

    sret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_START,
            *started_hart_id, 0, 0, 0, 0, 0);

    ret = sbi_error_map(VAL_VERBOSE_DEBUG, "hsm_hart_start return", sret.error);

    hsm_hart_get_status(NULL);

    return ret;
}
