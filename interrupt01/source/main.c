#include "gpio.h"
#include "clock.h"

void dummy ( unsigned int i )
{
  int a = i;
}

void pause(int t) {
    // Pause for about t ms
    int i;
    for (;t>0;t--) {
        for (i=5000;i>0;i--) dummy(i);
    }
}

static void audio_init(void)
{
  gpio_function_select(40, GPIO_ALT_0);
  gpio_function_select(45, GPIO_ALT_0);

  pause(2);
  clock_configure(CLOCK_OSCILLATOR, 2.0);
  pause(2);

  pwm_disable();
  pwm_set_range(0x400, 0x400); 
  pwm_enable(2);

  pause(2);
}

int audio_play()
{
  int i=0;
  audio_init();

  while (1) {
    pwm_fifo_put(20*(i & 0x1f));
    i++;
  }
}

int value = 0;
void led_toggle(void)
{
  if (value == 0)
    value = 1;
  else
    value = 0;

  gpio_set(16, value);
}

enum {
  SYSTEM_TIMER_BASE = 0x20003000,
  SYSTEM_TIMER_CLO = (SYSTEM_TIMER_BASE + 0x4),
};

void Wait(unsigned ticks)
{
  volatile unsigned* addr = (unsigned*) SYSTEM_TIMER_CLO;
  unsigned current_time = *addr;
  unsigned target = current_time + ticks;
  while (current_time < target) {
    current_time = *addr;
  }
}

//static volatile unsigned * irq_enable_basic = (volatile unsigned *) 0x2000b218;
static volatile unsigned * irq_enable_1 = (volatile unsigned *) 0x2000b210;

#define CS  (* (volatile unsigned *)(0x20003000))
#define CLO (* (volatile unsigned *)(0x20003004))
#define C1  (* (volatile unsigned *)(0x20003010))

/**
 * Assembler function for turning on irq in the CPSR register
 * 
 *   cpsie i
 */
extern void enable_irq(void);
volatile unsigned hit;

void main()
{
  gpio_function_select(16, GPIO_OUTPUT);
  gpio_set(16, 0); // 0 turns led on

  hit = 0;

  unsigned interval = 0x00080000;
  unsigned rx = CLO;
  rx += interval;
  CS = 0x2; // Clear status for Match 1 register
  C1 = rx;

  *irq_enable_1 = 0x2; // Enable System Timer IRQ (Where is this documented?)
  enable_irq();

  while (1)
  {
    if (hit)
    {
      led_toggle();
      Wait(50000);
    }
  }
// Enable 
//  audio_play();
}

void c_irq_handler ( void )
{
  hit = 1;
  led_toggle();
  gpio_set(16, 1);

  unsigned interval = 0x00080000;
  unsigned rx = CLO;
  rx += interval;
  CS = 0x2; // Clear status for Match 1 register
  C1 = rx;  
}
