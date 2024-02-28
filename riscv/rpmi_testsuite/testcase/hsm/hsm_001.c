#include "../hsm.h"

int hsm_hart_get_status(unsigned long * started_hart_id)
{
    struct sbiret sret;
    int ret;

    for (unsigned long hartid = 0 ; hartid < expected_hsm_nums; hartid++) {

        val_print(VAL_VERBOSE_DEBUG, "hartid = %lu ", hartid);

        sret = sbi_ecall(SBI_EXT_HSM, SBI_EXT_HSM_HART_STATUS,
                hartid, 0, 0, 0, 0, 0);

        ret = sbi_error_map(VAL_VERBOSE_DEBUG, "hsm_hart_get_status return", sret.error);

        switch (sret.value) {
            case SBI_HSM_STATE_STARTED:
                if (started_hart_id)
                    *started_hart_id = hartid;
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_STARTED)\n", sret.value);
                break;
            case SBI_HSM_STATE_STOPPED:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_STOPPED)\n", sret.value);
                break;
            case SBI_HSM_STATE_START_PENDING:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_START_PENDING)\n", sret.value);
                break;
            case SBI_HSM_STATE_STOP_PENDING:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_STOP_PENDING)\n", sret.value);
                break;
            case SBI_HSM_STATE_SUSPENDED:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_SUSPENDED)\n", sret.value);
                break;
            case SBI_HSM_STATE_SUSPEND_PENDING:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_SUSPEND_PENDING)\n", sret.value);
                break;
            case SBI_HSM_STATE_RESUME_PENDING:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (SBI_HSM_STATE_RESUME_PENDING)\n", sret.value);
                break;
            default:
                val_print(VAL_VERBOSE_DEBUG, "sret.value = %ld (Undefined)\n", sret.value);
                ret = VAL_ERROR;
        }
    }

    return ret;
}
