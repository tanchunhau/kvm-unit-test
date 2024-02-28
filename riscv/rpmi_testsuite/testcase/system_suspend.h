#ifndef __SYSTEM_SUSPEND_H__
#define __SYSTEM_SUSPEND_H__

//https://github.com/ventanamicro/linux/commit/5b745e53f5527dc7cff997b9554e484caf81c6f9

#include "../val/val_interface.h"

enum sbi_ext_susp_fid {
    SBI_EXT_SUSP_SYSTEM_SUSPEND = 0,
};

enum sbi_ext_susp_sleep_type {
    SBI_SUSP_SLEEP_TYPE_SUSPEND_TO_RAM = 0,
    SBI_SUSP_SLEEP_TYPE_INVALID = 1000000,
};

void test_system_suspend(void);
int system_suspend_probe_ext(void);
int system_suspend_neg_s2ram(void);

#endif /* __SYSTEM_SUSPEND_H__ */
