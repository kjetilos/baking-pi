#include "clock.h"

#define PASSWORD  0x5A000000
#define KILL            0x20
#define ENABLE          0x10
#define MASH_1         0x200

typedef volatile unsigned reg32;

struct clock
{
  reg32 control;
  reg32 divisor;
};

static struct clock * clock = (struct clock *)0x201010a0;

/**
 * Calculates the binary represenation of the 
 * fractional part of a float input argument
 * using a certain number of bits. 
 */
static int fraction(float f, int precision)
{
  int result = 0;
  float rest = f - (int)f;
  while (precision) {
    result = result << 1;
    rest = rest * 2;
    if (rest >= 1.0)
    {
      result = result | 1;
      rest = rest - 1.0;
    }

    precision--;
  }

  return result;
}

void clock_configure(clock_source source, float divider)
{
  int idiv = (int) divider;
  int fdiv = fraction(divider, 12);

  clock->control = PASSWORD | KILL;
  clock->divisor = PASSWORD | (idiv << 12) | fdiv;
  clock->control = PASSWORD | MASH_1 | ENABLE | source;
}
