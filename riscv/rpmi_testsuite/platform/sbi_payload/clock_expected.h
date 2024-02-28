#ifndef __CLOCK_EXPECTED_H__
#define __CLOCK_EXPECTED_H__

static const bool has_clock_srvgrp = true;
static const int expected_clock_tpid = 0x0a;
static const int expected_clock_nums = 3;

static struct sbi_rpxy_clk expected_clock_attribute[] = {
    // id, num_rates, transition_latency, format, clock_rates, name
    { 0, 4, 100, SBI_RPXY_CLK_DISCRETE, .rates = &(union sbi_rpxy_clk_rates){.discrete = {2469211230296036727UL, 18369583293460758255UL, 12302652056957900408UL, 12297829379896054033UL}}, "uartclk"},
    { 1, 6, 200, SBI_RPXY_CLK_DISCRETE, .rates = &(union sbi_rpxy_clk_rates){.discrete = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL}}, "pllclk"},
    { 2, 3, 300, SBI_RPXY_CLK_LINEAR,   .rates = &(union sbi_rpxy_clk_rates){.linear = {.min = 2459565876208275729UL, .max = 13527612320434006698UL, .step = 1229782938247303441UL}}, "gpuclk"}
};

inline static struct sbi_rpxy_clk* get_expected_clock_attributes(int index)
{
    return &expected_clock_attribute[index];
}

#endif /* __CLOCK_EXPECTED_H__ */
