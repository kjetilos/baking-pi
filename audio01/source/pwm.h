#pragma once

void pwm_disable(void);
void pwm_enable(int channels);
void pwm_set_range(int range1, int range2);
unsigned pwm_status(void);
void pwm_fifo_put(unsigned value);
