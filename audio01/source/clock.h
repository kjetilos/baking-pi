#pragma once

typedef enum clock_source 
{
  CLOCK_OSCILLATOR = 1,
  CLOCK_PLLA = 4,
  CLOCK_PLLC = 5,
  CLOCK_PLLD = 6,
} clock_source;

void clock_configure(clock_source source, float divider);
