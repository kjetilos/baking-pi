#include <stdint.h>
#include <stdbool.h>

typedef volatile uint32_t reg32;

typedef struct Mailbox
{
  reg32 read;           // 0x2000B880
  reg32 pad_1;          // 0x2000B884
  reg32 pad_2;          // 0x2000B888
  reg32 pad_3;          // 0x2000B88C
  reg32 poll;           // 0x2000B890
  reg32 sender;         // 0x2000B894
  reg32 status;         // 0x2000B898
  reg32 configuration;  // 0x2000B89C
  reg32 write;          // 0x2000B8A0
} Mailbox;

static Mailbox* mailbox = (Mailbox * const) 0x2000B880;

void MailboxWrite(uint32_t message, uint32_t channel)
{
  if (message & 0xf != 0 || channel > 15)
    return;

  uint32_t write_flag = 1;
  while ( write_flag != 0 )
    write_flag = mailbox->status & 0x80000000;

  uint32_t value = message + channel;
  mailbox->write = value;
}

uint32_t MailboxRead(uint32_t channel)
{
  if (channel > 15)
    return;
  
  uint32_t mail = 0;

  while ( true ) {
    uint32_t read_flag = 1;
    while ( read_flag != 0 )
      read_flag = mailbox->status & 0x40000000;
    
    mail = mailbox->read;
    if ((mail & 0xf) == channel)
      break;
  }

  return mail & 0xfffffff0;
}
