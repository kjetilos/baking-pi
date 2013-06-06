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
static const uint32_t MAILBOX_FULL  = 0x80000000;
static const uint32_t MAILBOX_EMPTY = 0x40000000;

void MailboxWrite(uint32_t message, uint32_t channel)
{
  if (message & 0xf != 0 || channel > 15)
    return;

  uint32_t full_flag = 1;
  while ( full_flag != 0 )
    full_flag = mailbox->status & MAILBOX_FULL;

  uint32_t value = message + channel;
  mailbox->write = value;
}

uint32_t MailboxRead(uint32_t channel)
{
  if (channel > 15)
    return;
  
  uint32_t mail = 0;

  while ( true ) {
    uint32_t empty_flag = 1;
    while ( empty_flag != 0 )
      empty_flag = mailbox->status & MAILBOX_EMPTY;
    
    mail = mailbox->read;
    if ((mail & 0xf) == channel)
      break;
  }

  return mail & 0xfffffff0;
}
