#ifndef _SIM868_GSM_H_
#define _SIM868_GSM_H_

#include "atterminal.h"

#include <stdbool.h>

typedef enum _SIM868GSMResponse_
{
	SIM868_GSM_FUNC = 0x3C05AEFF, // CFUN
	SIM868_GSM_PIN  = 0x754EDBE9, // CPIN
} SIM868GSMResponse;

typedef enum _SIM868GSMFunctionality_
{
	SIM868_GSM_FUNC_MINIMUM = 0,
	SIM868_GSM_FUNC_FULL    = 1,
	SIM868_GSM_FUNC_NO_RF   = 4,
} SIM868GSMFunctionality;

void SIM868_GSM_Functionality(ATTerminal* at, SIM868GSMFunctionality func);
void SIM868_GSM_EnterPin(ATTerminal* at, char* pin);

#endif
