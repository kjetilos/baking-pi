#include "pwm.h"

#define CHANNEL_2_USEFIFO    0x2000
#define CHANNEL_2_ENABLE     0x0100
#define CHANNEL_1_USEFIFO    0x0020
#define CHANNEL_1_ENABLE     0x0001
#define CLEAR_FIFO           0x0040

typedef volatile unsigned reg32;

struct pwm
{
  reg32 control;
  reg32 status;
  reg32 dma;
  reg32 __pad0;
  reg32 range1;
  reg32 data1;
  reg32 fifo;
  reg32 __pad1;
  reg32 range2;
  reg32 data2;
};

static struct pwm * pwm = (struct pwm *) 0x2020c000;

void pwm_disable(void)
{
  pwm->control = 0;
}

void pwm_enable(int channels)
{
  if (channels == 2)
  {
    pwm->control = 
        CHANNEL_2_USEFIFO |
        CHANNEL_2_ENABLE  |
        CLEAR_FIFO        |
        CHANNEL_1_USEFIFO |
        CHANNEL_1_ENABLE  ;
  }
  else if (channels == 1)
  {
    pwm->control = 
        CLEAR_FIFO        |
        CHANNEL_1_USEFIFO |
        CHANNEL_1_ENABLE  ;
  }
}

void pwm_set_range(int range1, int range2)
{
  pwm->range1 = range1;
  pwm->range2 = range2;
}

unsigned pwm_status(void)
{
  return pwm->status;
}

/**
 * 1 - fifo is full
 * 0 - fifo is not full
 */
int pwm_fifo_full(void)
{
  return pwm->status & 0x1;
}

void pwm_fifo_put(unsigned value)
{
  while (pwm_fifo_full())
    ;
  pwm->fifo = value;
}
