#ifndef __VAL_INTERFACE_H__
#define __VAL_INTERFACE_H__

#include <libcflat.h>
#include <stdlib.h>
#include <asm/sbi.h>
#include "rpmi.h"

#define VAL_SUCCESS 0
#define VAL_ERROR -1

#define VAL_VERBOSE_INFO  0
#define VAL_VERBOSE_DEBUG 1

int val_init(void);

void val_print(int verbose_setting, const char *format, ...);

int val_srvgrp_probe(u32 transportid, u32 srvgrpid, unsigned long *val);

int val_send_normal_message(unsigned long transportid, unsigned long srvgrpid, unsigned long srvid,
                                 void *tx, unsigned long tx_msglen,
                                 void *rx, unsigned long *rx_msglen);

int rpmi_status_map(int verbose_setting, const char* msg, int status);

// for sbi platform usage
int sbi_error_map(int verbose_setting, const char* msg, int err);

struct sbi_rpxy* get_rpxy(void);

#endif /* __VAL_INTERFACE_H__ */
