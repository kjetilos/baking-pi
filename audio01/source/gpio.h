#pragma once

enum gpio_function
{
  GPIO_INPUT = 0x0,
  GPIO_OUTPUT = 0x1,
  GPIO_ALT_0 = 0x4,
  GPIO_ALT_1 = 0x5,
  GPIO_ALT_2 = 0x6,
  GPIO_ALT_3 = 0x7,
  GPIO_ALT_4 = 0x3,
  GPIO_ALT_5 = 0x2
};

void gpio_function_select(unsigned pin, enum gpio_function function);
void gpio_set(unsigned pin, unsigned val);
