#pragma once
#include <stdint.h>

void MailboxWrite(uint32_t message, uint32_t channel);
uint32_t MailboxRead(uint32_t channel);
