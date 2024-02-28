#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "../val/val_interface.h"
#include "../platform/sbi_payload/clock_expected.h"

void test_clock(void);
int clock_srvgrp_probe(void);
int clock_query_quantity(void);
int clock_query_attrs(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_query_supported_rates(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);

// negative test
int clock_negative_srvgrp_probe(void);
int clock_negative_query_quantity(void);
int clock_negative_query_attrs(void);
int clock_negative_query_supported_rates(void);
int clock_negative_query_supported_rates_wrong_rate_index(void);

#endif /* __CLOCK_H__ */
