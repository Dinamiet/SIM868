#ifndef _SIM868_SMS_H_
#define _SIM868_SMS_H_

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum _SIM868SMSResponse_
{
	SIM868_SMS_READY = 0xEE605F1D, // SMS Ready
	SIM868_SMS_SENT  = 0xC6536377, // CMGS
} SIM868SMSResponse;

void SIM868_SMS_SetFormat(ATTerminal* at, bool text);
void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg);

uint8_t SIM868_SMS_ParseSend(char* info);

#endif
