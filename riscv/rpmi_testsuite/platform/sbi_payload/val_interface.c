#include <alloc.h>
#include "../../val/val_interface.h"

#define SHMEM_PAGE_SIZE 4096

struct sbi_rpxy g_rpxy;

int val_init(void)
{
    val_print(VAL_VERBOSE_INFO, "001 : Set shmem\n");
    struct sbiret sret;
    g_rpxy.shmem = memalign(SHMEM_PAGE_SIZE, SHMEM_PAGE_SIZE);
    g_rpxy.shmem_phys = (unsigned long long)g_rpxy.shmem;
    g_rpxy.active = true;

    sret = sbi_ecall(SBI_EXT_RPXY, SBI_EXT_RPXY_SETUP_SHMEM,
                        SHMEM_PAGE_SIZE, g_rpxy.shmem_phys, 0, 0, 0, 0);

    return sbi_error_map(VAL_VERBOSE_DEBUG, "Configure shmem return", sret.error);
}

void val_print(int verbose_setting, const char *format, ...)
{
    #define SBI_EXT_DBCN                0x4442434E
    #define SBI_EXT_DBCN_CONSOLE_WRITE  0x0

    if (VAL_VERBOSE_CONFIG >= verbose_setting) {
        va_list args;
        va_start(args, format);  // Initialize va_list

        char str[512];
        int n = vsnprintf(str, 512, format, args);

        // int n = snprintf(NULL, 0, format, args);
        //char* str = (char*)malloc(n + 1);
        // n = vsnprintf(str, n + 1, format, args);

        va_end(args);            // Clean up resources
        sbi_ecall(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOLE_WRITE,
          n, (unsigned long)str, 0, 0, 0, 0);
        //free(str);
    }
}

struct sbi_rpxy* get_rpxy(void)
{
    return &g_rpxy;
}

int val_srvgrp_probe(u32 transportid, u32 srvgrpid, unsigned long *val)
{
    struct sbiret sret;

    sret = sbi_ecall(SBI_EXT_RPXY, SBI_EXT_RPXY_PROBE,
                transportid, srvgrpid, 0, 0, 0, 0);

    if (val)
        *val = sret.value;

    return sret.error;
}

int val_send_normal_message(unsigned long transportid, unsigned long srvgrpid, unsigned long srvid,
                                 void *tx, unsigned long tx_msglen,
                                 void *rx, unsigned long *rx_msglen)
{
    struct sbiret sret;
    sret.error = 0;
    sret.value = 0;

    //dest, source ,len
    memcpy(g_rpxy.shmem, tx, tx_msglen);

    /* Shared memory is copied with message data at 0x0 offset */
    sret = sbi_ecall(SBI_EXT_RPXY, SBI_EXT_RPXY_SEND_NORMAL_MSG,
                         transportid, srvgrpid, srvid, tx_msglen, 0, 0);

    if (!sret.error && rx) {
        memcpy(rx, g_rpxy.shmem, sret.value);
        val_print(VAL_VERBOSE_DEBUG, "send_normal_message sret.value = %ld ( ", sret.value);
        unsigned char* value = (unsigned char*) g_rpxy.shmem;

        int i = 0;
        for (i = 0; i < sret.value; i++){
            val_print(VAL_VERBOSE_DEBUG, "%d ", (int)value[i]);
        }
        val_print(VAL_VERBOSE_DEBUG, ")\n");

        if (rx_msglen) {
            *rx_msglen = sret.value;
        }
    }

    return sret.error;//sbi_error_map(VAL_VERBOSE_DEBUG, "send_normal_message return", sret.error);
}

int rpmi_status_map(int verbose_setting, const char* msg, int status)
{
    switch (status)
    {
        case RPMI_SUCCESS:
            val_print(verbose_setting, "%s RPMI_SUCCESS (%d)\n", msg, RPMI_SUCCESS);
            return VAL_SUCCESS;
        case RPMI_ERROR_FAILED:
            val_print(verbose_setting, "%s RPMI_ERROR_FAILED (%d)\n", msg, RPMI_ERROR_FAILED);
            return VAL_ERROR;
        case RPMI_ERROR_NOT_SUPPORTED:
            val_print(verbose_setting, "%s RPMI_ERROR_NOT_SUPPORTED (%d)\n", msg, RPMI_ERROR_NOT_SUPPORTED);
            return VAL_ERROR;
        case RPMI_ERROR_INVALID_PARAMETER:
            val_print(verbose_setting, "%s RPMI_ERROR_INVALID_PARAMETER (%d)\n", msg, RPMI_ERROR_INVALID_PARAMETER);
            return VAL_ERROR;
        case RPMI_ERROR_DENIED:
            val_print(verbose_setting, "%s RPMI_ERROR_DENIED (%d)\n", msg, RPMI_ERROR_DENIED);
            return VAL_ERROR;
        case RPMI_ERROR_NOT_FOUND:
            val_print(verbose_setting, "%s RPMI_ERROR_NOT_FOUND (%d)\n", msg, RPMI_ERROR_NOT_FOUND);
            return VAL_ERROR;
        case RPMI_ERROR_OUT_OF_RANGE:
            val_print(verbose_setting, "%s RPMI_ERROR_OUT_OF_RANGE (%d)\n", msg, RPMI_ERROR_OUT_OF_RANGE);
            return VAL_ERROR;
        case RPMI_ERROR_OUT_OF_RESOURCE:
            val_print(verbose_setting, "%s RPMI_ERROR_OUT_OF_RESOURCE (%d)\n", msg, RPMI_ERROR_OUT_OF_RESOURCE);
            return VAL_ERROR;
        case RPMI_ERROR_HW_FAULT:
            val_print(verbose_setting, "%s RPMI_ERROR_HW_FAULT (%d)\n", msg, RPMI_ERROR_HW_FAULT);
            return VAL_ERROR;
        case RPMI_ERROR_BUSY:
            val_print(verbose_setting, "%s RPMI_ERROR_BUSY (%d)\n", msg, RPMI_ERROR_BUSY);
            return VAL_ERROR;
        case RPMI_ERROR_TIMEOUT:
            val_print(verbose_setting, "%s RPMI_ERROR_TIMEOUT (%d)\n", msg, RPMI_ERROR_TIMEOUT);
            return VAL_ERROR;
        case RPMI_ERROR_COMMS:
            val_print(verbose_setting, "%s RPMI_ERROR_COMMS (%d)\n", msg, RPMI_ERROR_COMMS);
            return VAL_ERROR;
        case RPMI_ERROR_ALREADY:
            val_print(verbose_setting, "%s RPMI_ERROR_ALREADY (%d)\n", msg, RPMI_ERROR_ALREADY);
            return VAL_ERROR;
        case RPMI_ERROR_EXTENSION:
            val_print(verbose_setting, "%s RPMI_ERROR_EXTENSION (%d)\n", msg, RPMI_ERROR_EXTENSION);
            return VAL_ERROR;
        default:
            val_print(verbose_setting, "%s Undefined (%d)\n", msg, status);
            return VAL_ERROR;
    }
}

int sbi_error_map(int verbose_setting, const char* msg, int err)
{
    switch (err)
    {
        case SBI_SUCCESS:
            val_print(verbose_setting, "%s SBI_SUCCESS (%d)\n", msg, SBI_SUCCESS);
            return VAL_SUCCESS;
        case SBI_ERR_FAILURE:
            val_print(verbose_setting, "%s SBI_ERR_FAILURE (%d)\n", msg, SBI_ERR_FAILURE);
            return VAL_ERROR;
        case SBI_ERR_NOT_SUPPORTED:
            val_print(verbose_setting, "%s SBI_ERR_NOT_SUPPORTED (%d)\n", msg, SBI_ERR_NOT_SUPPORTED);
            return VAL_ERROR;
        case SBI_ERR_INVALID_PARAM:
            val_print(verbose_setting, "%s SBI_ERR_INVALID_PARAM (%d)\n", msg, SBI_ERR_INVALID_PARAM);
            return VAL_ERROR;
        case SBI_ERR_DENIED:
            val_print(verbose_setting, "%s SBI_ERR_DENIED (%d)\n", msg, SBI_ERR_DENIED);
            return VAL_ERROR;
        case SBI_ERR_INVALID_ADDRESS:
            val_print(verbose_setting, "%s SBI_ERR_INVALID_ADDRESS (%d)\n", msg, SBI_ERR_INVALID_ADDRESS);
            return VAL_ERROR;
        case SBI_ERR_ALREADY_AVAILABLE:
            val_print(verbose_setting, "%s SBI_ERR_ALREADY_AVAILABLE (%d)\n", msg, SBI_ERR_ALREADY_AVAILABLE);
            return VAL_ERROR;
        case SBI_ERR_ALREADY_STARTED:
            val_print(verbose_setting, "%s SBI_ERR_ALREADY_STARTED (%d)\n", msg, SBI_ERR_ALREADY_STARTED);
            return VAL_ERROR;
        case SBI_ERR_ALREADY_STOPPED:
            val_print(verbose_setting, "%s SBI_ERR_ALREADY_STOPPED (%d)\n", msg, SBI_ERR_ALREADY_STOPPED);
            return VAL_ERROR;
        case SBI_ERR_INVALID_STATE:
            val_print(verbose_setting, "%s SBI_ERR_INVALID_STATE (%d)\n", msg, SBI_ERR_INVALID_STATE);
            return VAL_ERROR;
        case SBI_ERR_BAD_RANGE:
            val_print(verbose_setting, "%s SBI_ERR_BAD_RANGE (%d)\n", msg, SBI_ERR_BAD_RANGE);
            return VAL_ERROR;
        case SBI_ERR_BUSY:
            val_print(verbose_setting, "%s SBI_ERR_BUSY (%d)\n", msg, SBI_ERR_BUSY);
            return VAL_ERROR;
        default:
            val_print(verbose_setting, "%s Undefined (%d)\n", msg, err);
            return VAL_ERROR;
    }
}
