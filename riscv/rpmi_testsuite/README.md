**RPMI test suite**
===================================

Introduction
-------
This document outlines the test scenarios and how individual test cases are implemented in the current version of the RPMI test suite.

Compile:
-------
> git clone https://github.com/tanchunhau/kvm-unit-test.git -b rpmi_test
>
> cd kvm-unit-test
>
> ./configure
>
> make rpmi=on VERBOSE=1

VERBOSE = 0 ( less info), 1 (more info)

----------

Clock Service Group Tests
----------
This section outlines the test specification for RPMI Clock Service Group

| Test ID    | Test Intent           | Verification Steps  | Comments/Commands Used  | Implemented  |
| ---------- | --------------------- | ------------------- | ----------------------- | ------------ |
| 101 | Clock service group probe | Check if SBI_SUCCESS is returned and max_msg_len has value | SBI_EXT_RPXY_PROBE | Yes |
| 102 | Query clock quantity | Check if return clock quantity matches expected quantity | RPMI_CLK_SRV_GET_SYSTEM_CLOCKS | Yes |
| 103 | Query clock attribute | Check if return clock attribute matches expected attribute | RPMI_CLK_SRV_GET_ATTRIBUTES | Yes |
| 104 | Query clock supported rate | Check if return clock supported rate matches expected supported rate | RPMI_CLK_SRV_GET_SUPPORTED_RATES | Yes |
| 105 (N) | Clock service group probe with wrong transport id | Check if SBI_ERR_NOT_SUPPORTED is returned | RPMI_SRVGRP_CLOCK | Yes |
| 106 (N) | Query clock quantity with wrong transport id | Check if SBI_ERR_NOT_SUPPORTED is returned  | RPMI_CLK_SRV_GET_SYSTEM_CLOCKS | Yes |
| 107 (N) | Query clock attribute with wrong clock id | Check if RPMI_ERROR_NOT_FOUND is returned | RPMI_CLK_SRV_GET_ATTRIBUTES | Yes |
| 108 (N) | Query clock supported rate with wrong clock clock id | Check if RPMI_ERROR_NOT_FOUND is returned | RPMI_CLK_SRV_GET_SUPPORTED_RATES | Yes |
| 109 (N) | Query clock supported rate with wrong clock rate index | Check if RPMI_ERROR_OUT_OF_RANGE is returned | RPMI_CLK_SRV_GET_SUPPORTED_RATES | Yes |

(N) = negative test

HSM Ext Tests (Hart State Management)
----------
This section outlines the test specification for HSM Ext Tests

| Test ID    | Test Intent           | Verification Steps  | Comments/Commands Used  | Implemented  |
| ---------- | --------------------- | ------------------- | ----------------------- | ------------ |
| 201 | HSM Ext probe | Check if SBI_SUCCESS is returned | SBI_EXT_BASE_PROBE_EXT | Yes |
| 202 | Query harts status | Check if harts status is returned successfully | SBI_EXT_HSM_HART_STATUS | Yes |
| 203 | Start a hart | Check if able to start a hart successfully | SBI_EXT_HSM_HART_START | Yes |
| 204 (N) | Start a hart with wrong hart id | Check if SBI_ERR_INVALID_PARAM is returned | SBI_EXT_HSM_HART_START | Yes |

(N) = negative test

SRST Ext Tests (System Reset)
----------
This section outlines the test specification for SRST Ext Tests

| Test ID    | Test Intent           | Verification Steps  | Comments/Commands Used  | Implemented  |
| ---------- | --------------------- | ------------------- | ----------------------- | ------------ |
| 301 | SRST Ext probe | Check if SBI_SUCCESS is returned | SBI_EXT_BASE_PROBE_EXT | Yes |
| 302 (N) | Shutdown with invalid reason | Check if SBI_ERR_INVALID_PARAM is returned | SBI_SRST_RESET_TYPE_SHUTDOWN | Yes |
| 303 (N) | Cold reboot with invalid reason | Check if SBI_ERR_INVALID_PARAM is returned | SBI_SRST_RESET_TYPE_COLD_REBOOT | Yes |
| 304 (N) | Warn reboot with invalid reason | Check if SBI_ERR_INVALID_PARAM is returned | SBI_SRST_RESET_TYPE_WARM_REBOOT | Yes |
| 305 (N) | reboot with invalid type | Check if SBI_ERR_INVALID_PARAM is returned | SBI_EXT_SRST_RESET | Yes |

(N) = negative test

SUSP Ext Tests (System Suspend)
----------
This section outlines the test specification for SUSP Ext Tests

| Test ID    | Test Intent           | Verification Steps  | Comments/Commands Used  | Implemented  |
| ---------- | --------------------- | ------------------- | ----------------------- | ------------ |
| 401 | SUSP Ext probe | Check if SBI_SUCCESS is returned | SBI_EXT_BASE_PROBE_EXT | Yes |
| 402 (N) | Suspend to RAM with invalid type | Check if SBI_ERR_INVALID_PARAM is returned | SBI_EXT_SUSP_SYSTEM_SUSPEND | Yes |

(N) = negative test

CPPC Ext Tests (Collaborative Processor Performance Control)
----------
This section outlines the test specification for CPPC Ext Tests

| Test ID    | Test Intent           | Verification Steps  | Comments/Commands Used  | Implemented  |
| ---------- | --------------------- | ------------------- | ----------------------- | ------------ |
| 501 | CPPC Ext probe | Check if SBI_SUCCESS is returned | SBI_EXT_BASE_PROBE_EXT | Yes |
| 502 | Read register value | Check if register value is returned successfully | SBI_CPPC_READ | Yes |
| 503 | Write register value | Check if register value is written successfully | SBI_CPPC_WRITE | Yes |

(N) = negative test


