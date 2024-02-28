#include "../cppc.h"

int cppc_write(void)
{
    struct sbiret sret;
    int ret = VAL_SUCCESS;

    int count =  sizeof(expected_write_regs) / sizeof(expected_write_regs[0]);

    int index = 0;
    for (index = 0; index < count; index++) {
        val_print(VAL_VERBOSE_DEBUG, "cppc_write regs = %lu, value = %ld\n", expected_write_regs[index], expected_write_values[index]);
        sret = sbi_ecall(SBI_EXT_CPPC, SBI_CPPC_WRITE, expected_write_regs[index], expected_write_values[index], 0, 0, 0, 0);
        if (sbi_error_map(VAL_VERBOSE_DEBUG, "cppc_write return", sret.error) != VAL_SUCCESS) {
            ret = VAL_ERROR;
        }
    }

    return ret;
}
