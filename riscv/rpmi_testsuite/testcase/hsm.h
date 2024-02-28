#ifndef __HSM_H__
#define __HSM_H__

#include <asm/sbi.h>
#include "../val/val_interface.h"
#include "../platform/sbi_payload/hsm_expected.h"

enum sbi_hsm_hart_state {
    SBI_HSM_STATE_STARTED = 0,
    SBI_HSM_STATE_STOPPED,
    SBI_HSM_STATE_START_PENDING,
    SBI_HSM_STATE_STOP_PENDING,
    SBI_HSM_STATE_SUSPENDED,
    SBI_HSM_STATE_SUSPEND_PENDING,
    SBI_HSM_STATE_RESUME_PENDING,
};

void test_hsm(void);
int hsm_probe_ext(void);
int hsm_hart_get_status(unsigned long* started_hart_id);
int hsm_hart_start(unsigned long* started_hart_id);
int hsm_hart_stop(unsigned long* started_hart_id);
int hsm_negative_hart_start(void);

#endif /* __HSM_H__ */
