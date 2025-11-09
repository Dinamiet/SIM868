#include "defines.h"
#include "sim868_sms.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_SMS_SetFormat(ATTerminal* at, bool text)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGF=%d", text);
	ATTerminal_SendCommand(at, command);
}

void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGS=\"%s\"", number);
	ATTerminal_SendCommand(at, command);
	ATTerminal_Wait(at, "> ");
	sprintf(command, "%s\x1A", msg);
	ATTerminal_SendCommand(at, command);
}

void SIM868_SMS_ReadMsg(ATTerminal* at, uint8_t index)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGR=%d", index);
	ATTerminal_SendCommand(at, command);
}

void SIM868_SMS_DeleteMsg(ATTerminal* at, uint8_t index)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGD=%d", index);
	ATTerminal_SendCommand(at, command);
}

uint8_t SIM868_SMS_ParseSend(char* info)
{
	return atoi(info);
}

uint8_t SIM868_SMS_ParseNewMsg(char* info)
{
	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Memory info

	// Index
	token = strsep(&rest, ",");
	return atoi(token);
}

char* SIM868_SMS_ParseMsgSender(char* info)
{
	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Read status

	// Sender Number
	token = strsep(&rest, ",");
	strsep(&token, "\"");
	return strsep(&token, "\"");
}
