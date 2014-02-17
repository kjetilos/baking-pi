#include "gpio.h"

extern void dummy ( unsigned int );

#define BCM2708_PERI_BASE 0x20000000
#define GPIO_BASE         (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define PWM_BASE          (BCM2708_PERI_BASE + 0x20C000) /* PWM controller */
#define CLOCK_BASE        (BCM2708_PERI_BASE + 0x101000)
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
#define BCM2835_PWM_CONTROL 0
#define BCM2835_PWM_STATUS  1
#define BCM2835_PWM0_RANGE  4
#define BCM2835_PWM0_DATA   5
#define BCM2835_PWM_FIFO    6
#define BCM2835_PWM1_RANGE  8
#define BCM2835_PWM1_DATA   9
#define BCM2835_PWMCLK_CNTL   40
#define BCM2835_PWMCLK_DIV    41
#define BCM2835_PWM1_MS_MODE    0x8000  /*  Run in MS mode                   */
#define BCM2835_PWM1_USEFIFO    0x2000  /*  Data from FIFO                   */
#define BCM2835_PWM1_REVPOLAR   0x1000  /* Reverse polarity             */
#define BCM2835_PWM1_OFFSTATE   0x0800  /* Ouput Off state             */
#define BCM2835_PWM1_REPEATFF   0x0400  /* Repeat last value if FIFO empty   */
#define BCM2835_PWM1_SERIAL     0x0200  /* Run in serial mode             */
#define BCM2835_PWM1_ENABLE     0x0100  /* Channel Enable             */
#define BCM2835_PWM0_MS_MODE    0x0080  /* Run in MS mode             */
#define BCM2835_PWM0_USEFIFO    0x0020  /* Data from FIFO             */
#define BCM2835_PWM0_REVPOLAR   0x0010  /* Reverse polarity             */
#define BCM2835_PWM0_OFFSTATE   0x0008  /* Ouput Off state             */
#define BCM2835_PWM0_REPEATFF   0x0004  /* Repeat last value if FIFO empty   */
#define BCM2835_PWM0_SERIAL     0x0002  /* Run in serial mode             */
#define BCM2835_PWM0_ENABLE     0x0001  /* Channel Enable             */
#define BCM2835_BERR  0x100
#define BCM2835_GAPO4 0x80
#define BCM2835_GAPO3 0x40
#define BCM2835_GAPO2 0x20
#define BCM2835_GAPO1 0x10
#define BCM2835_RERR1 0x8
#define BCM2835_WERR1 0x4
#define BCM2835_EMPT1 0x2
#define BCM2835_FULL1 0x1
#define PM_PASSWORD 0x5A000000
#define ERRORMASK (BCM2835_GAPO2 | BCM2835_GAPO1 | \
    BCM2835_RERR1 | BCM2835_WERR1)

volatile unsigned* gpio = (void*)GPIO_BASE;
volatile unsigned* pwm = (void*)PWM_BASE;
volatile unsigned* clk = (void*)CLOCK_BASE;

typedef volatile unsigned reg32;

typedef struct Clock
{
  reg32 CTL;
  reg32 DIV;
} Clock;

static Clock * sclk = (Clock *)0x201010a0;

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
  SET_GPIO_ALT(40, 0);
  SET_GPIO_ALT(45, 0);
  pause(2);
  sclk->CTL = PM_PASSWORD | (1 << 5); // stop clock

  int idiv = 2; // raspbian has idiv set as 16384
  *(clk + BCM2835_PWMCLK_DIV)  = PM_PASSWORD | (idiv<<12);
 
  sclk->CTL = PM_PASSWORD | 16 | 1; // enable + oscillator
                                                       // raspbian has this as plla
  pause(2);

  // disable PWM
  *(pwm + BCM2835_PWM_CONTROL) = 0;
 
  pause(2);

  *(pwm+BCM2835_PWM0_RANGE) = 0x400;
  *(pwm+BCM2835_PWM1_RANGE) = 0x400;

  *(pwm+BCM2835_PWM_CONTROL) =
        BCM2835_PWM1_USEFIFO |
        BCM2835_PWM1_ENABLE  |
        BCM2835_PWM0_USEFIFO |
        BCM2835_PWM0_ENABLE  | 1<<6;

  pause(2);
}

int audio_play()
{
  int i=0;
  long status;
  audio_init();

  while (1) {
    status =  *(pwm + BCM2835_PWM_STATUS);
    if (!(status & BCM2835_FULL1)) {
      *(pwm+BCM2835_PWM_FIFO) = 20*(i & 0x1f) ;
      i++;
    }
    if ((status & ERRORMASK)) {
      *(pwm+BCM2835_PWM_STATUS) = ERRORMASK;
    }
  }
}

void main()
{
  gpio_function_select(16, GPIO_OUTPUT);
  gpio_set(16, 0); // 0 turns led on

  audio_play();
}
