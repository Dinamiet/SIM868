#include "defines.h"
#include "sim868_sms.h"

#include <stdio.h>
#include <stdlib.h>

void SIM868_SMS_SetFormat(ATTerminal* at, bool text)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGF=%d", text);
	ATTerminal_SendCommand(at, command);
}

void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg)
{
	(void)msg;
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGS=\"%s\"", number);
	ATTerminal_SendCommand(at, command);
	ATTerminal_Wait(at, "> ");
	sprintf(command, "%s\x1A", msg);
	ATTerminal_SendCommand(at, command);
}

uint8_t SIM868_SMS_ParseSend(char* info)
{
	return atoi(info);
}
