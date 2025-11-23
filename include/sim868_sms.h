#ifndef _SIM868_SMS_H_
#define _SIM868_SMS_H_

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum _SIM868SMSResponse_
{
	SIM868_SMS_RESPONSE_READY    = 0xEE605F1D, // SMS Ready
	SIM868_SMS_RESPONSE_SENT     = 0xC6536377, // CMGS
	SIM868_SMS_RESPONSE_NEW_MSG  = 0x8789C36,  // CMTI
	SIM868_SMS_RESPONSE_MSG_DATA = 0xC55361E4, // CMGR
} SIM868SMSResponse;

typedef struct _SIM868SMSMessageInfo_
{
	char*  Sender;
	size_t Length;
} SIM868SMSMessageInfo;

void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg);
void SIM868_SMS_RequestReceivedMsg(ATTerminal* at, uint8_t index);
void SIM868_SMS_DeleteMsg(ATTerminal* at, uint8_t index);

uint8_t SIM868_SMS_ParseSend(char* info);
uint8_t SIM868_SMS_ParseNewMsg(char* info);
SIM868SMSMessageInfo SIM868_SMS_ParseMsgInfo(char* info);
size_t               SIM868_SMS_ReadMsg(ATTerminal* at, void* data, size_t size);

#endif
