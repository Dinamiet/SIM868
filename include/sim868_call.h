#ifndef _SIM868_CALL_H_
#define _SIM868_CALL_H_

#include "atterminal.h"

typedef enum _SIM868CallResponse_
{
	SIM868_CALL_RESPONSE_READY          = 0xC2026E92, // Call Ready
	SIM868_CALL_RESPONSE_RING           = 0xF54C2F6B, // RING
	SIM868_CALL_RESPONSE_IDENTIFICATION = 0x9063C3FB, // CLIP
} SIM868CallResponse;

void SIM868_Call_Accept(ATTerminal* at);
void SIM868_Call_Terminate(ATTerminal* at);
void SIM868_Call_Place(ATTerminal* at, char* number);

char* SIM868_Call_ParseIndentification(char* info);

#endif
