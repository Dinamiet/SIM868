#include "sim868_gsm.h"

#include <stdio.h>

#define MAX_COMMAND_SIZE 16

void SIM868_GSM_Functionality(ATTerminal* at, SIM868GSMFunctionality func)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CFUN=%d", func);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GSM_EnterPin(ATTerminal* at, char* pin)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CPIN=%s", pin);
	ATTerminal_SendCommand(at, command);
}
