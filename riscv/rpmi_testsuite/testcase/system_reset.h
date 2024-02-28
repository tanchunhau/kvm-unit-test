#ifndef __SYSTEM_RESET_H__
#define __SYSTEM_RESET_H__

#include "../val/val_interface.h"

enum sbi_ext_srst_fid {
    SBI_EXT_SRST_RESET = 0,
};

enum sbi_srst_reset_type {
    SBI_SRST_RESET_TYPE_SHUTDOWN = 0,
    SBI_SRST_RESET_TYPE_COLD_REBOOT,
    SBI_SRST_RESET_TYPE_WARM_REBOOT,
    SBI_SRST_RESET_TYPE_INVALID = 1000000,
};

enum sbi_srst_reset_reason {
    SBI_SRST_RESET_REASON_NONE = 0,
    SBI_SRST_RESET_REASON_SYS_FAILURE,
    SBI_SRST_RESET_REASON_INVALID = 1000000,
};

void test_system_reset(void);
int system_reset_probe_ext(void);
int system_reset_neg_shutdown(void);
int system_reset_neg_cold_reboot(void);
int system_reset_neg_warm_reboot(void);
int system_reset_neg_reboot_type(void);

#endif /* __SYSTEM_RESET_H__ */
