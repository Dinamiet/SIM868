#ifndef _SIM868_MISC_H_
#define _SIM868_MISC_H_

#include "atterminal.h"

#include <stdbool.h>

typedef enum _SIM868MiscResponse_
{
	SIM868_MISC_OK    = 0x85E4B82F,
	SIM868_MISC_ERROR = 0xDF22B531,
	SIM868_MISC_RDY   = 0xBCD1304E,
} SIM868MiscResponse;

void SIM868_Misc_CommandEcho(ATTerminal* at, bool echoEnabled);
void SIM868_Misc_Check(ATTerminal* at);

#endif
