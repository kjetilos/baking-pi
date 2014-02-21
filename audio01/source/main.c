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

void main()
{
  gpio_function_select(16, GPIO_OUTPUT);
  gpio_set(16, 0); // 0 turns led on

  audio_play();
}
