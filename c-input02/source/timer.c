#include "timer.h"

enum {
  SYSTEM_TIMER_BASE = 0x20003000,
  SYSTEM_TIMER_CLO = (SYSTEM_TIMER_BASE + 0x4),
};

void Wait(uint32_t ticks)
{
  volatile uint32_t* addr = (uint32_t*) SYSTEM_TIMER_CLO;
  uint32_t current_time = *addr;
  uint32_t target = current_time + ticks;
  while (current_time < target) {
    current_time = *addr;
  }
}
