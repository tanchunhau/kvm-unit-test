#include "../cppc.h"

int cppc_read(void)
{
    struct sbiret sret;
    int ret = VAL_SUCCESS;

    int count =  sizeof(expected_read_regs) / sizeof(expected_read_regs[0]);

    /*
    struct read_reg_resp {
        u32 status;
        u32 datal_low;
        u32 data_high;
    };
    */
    //struct read_reg_resp* resp = (struct read_reg_resp*)(get_rpxy());

    int i = 0;
    for (i = 0; i < count; i++) {
        sret = sbi_ecall(SBI_EXT_CPPC, SBI_CPPC_READ, expected_read_regs[i], 0, 0, 0, 0, 0);

       //val_print(VAL_VERBOSE_DEBUG, "read_reg_resp status = %ld\n", (long)resp->status);
       //val_print(VAL_VERBOSE_DEBUG, "read_reg_resp data_low = %lu\n", (unsigned long)resp->datal_low);
       //val_print(VAL_VERBOSE_DEBUG, "read_reg_resp data_high = %lu\n", (unsigned long)resp->data_high);

        val_print(VAL_VERBOSE_DEBUG, "Expected cppc_read regs = %lu, value = %ld\n", expected_read_regs[i], sret.value);
        val_print(VAL_VERBOSE_DEBUG, "  Actual cppc_read regs = %lu, value = %ld\n", expected_read_regs[i], expected_read_values[i]);

        if (sbi_error_map(VAL_VERBOSE_DEBUG, "cppc_read return", sret.error) != VAL_SUCCESS) {
            ret = VAL_ERROR;
        }

        if (sret.value != expected_read_values[i]) {
            ret = VAL_ERROR;
        }
    }

    return ret;
}
