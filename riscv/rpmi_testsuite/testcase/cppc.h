#ifndef __CPPC_H__
#define __CPPC_H__

//https://github.com/ventanamicro/qemu/commit/7ff69a091390bfaf66ee13e542f3986e8aa5ad27
//https://github.com/ventanamicro/linux/commit/c201e5e6281a61ba02a5c456508577caa4a5c8ef

#include "../val/val_interface.h"
#include "../platform/sbi_payload/cppc_expected.h"

#define SBI_CPPC_READ         0x1
#define SBI_CPPC_READ_HI      0x2
#define SBI_CPPC_WRITE        0x3

void test_cppc(void);
int cppc_probe_ext(void);
int cppc_read(void);
int cppc_write(void);

#endif /* __CPPC_H__ */
