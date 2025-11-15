#include "defines.h"
#include "sim868_sms.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg)
{
	char command[MAX_COMMAND_SIZE];
	ATTerminal_SendCommand(at, "AT+CMGF=1");
	sprintf(command, "AT+CMGS=\"%s\"", number);
	ATTerminal_SendCommand(at, command);
	ATTerminal_Wait(at, "> ");
	size_t length = sprintf(command, "%s\x1A", msg);
	ATTerminal_SendRaw(at, command, length);
}

void SIM868_SMS_RequestReceivedMsg(ATTerminal* at, uint8_t index)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGF=1;+CSDH=1;+CMGR=%d", index);
	ATTerminal_SendCommand(at, command);
}

void SIM868_SMS_DeleteMsg(ATTerminal* at, uint8_t index)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CMGD=%d", index);
	ATTerminal_SendCommand(at, command);
}

uint8_t SIM868_SMS_ParseSend(char* info) { return atoi(info); }

uint8_t SIM868_SMS_ParseNewMsg(char* info)
{
	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Memory info

	// Index
	token = strsep(&rest, ",");
	return atoi(token);
}

SIM868SMSMessageInfo SIM868_SMS_ParseMsgInfo(char* info)
{
	SIM868SMSMessageInfo msgInfo = {0};

	char* rest  = info;
	char* token = NULL;

	// Read status
	strsep(&rest, ",");

	// Sender Number
	token = strsep(&rest, ",");
	strsep(&token, "\"");
	msgInfo.Sender = strsep(&token, "\"");

	// Unknown field
	strsep(&rest, ",");

	// Date and time
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Service Provider field?
	strsep(&rest, ",");

	// Unknown field
	strsep(&rest, ",");

	// Length
	token = strsep(&rest, ",");
	if (token)
		msgInfo.Length = atoi(token);

	return msgInfo;
}

size_t SIM868_SMS_ReadMsg(ATTerminal* at, void* data, size_t size) { return ATTerminal_ReadRaw(at, data, size); }
