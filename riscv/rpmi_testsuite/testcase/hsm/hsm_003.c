#include "../hsm.h"

//---- this will cause shutdown ---//

int hsm_hart_stop(unsigned long* started_hart_id)
{
    int ret;

    struct sbiret sret;

    val_print(VAL_VERBOSE_DEBUG, "hsm_hart_stop (%lu) ", *started_hart_id);

    sret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_STOP,
            0, 0, 0, 0, 0, 0);

    ret = sbi_error_map(VAL_VERBOSE_DEBUG, "hsm_hart_stop return", sret.error);

    hsm_hart_get_status(NULL);

    return ret;
}
