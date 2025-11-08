#include "defines.h"
#include "sim868_call.h"

#include <stdio.h>
#include <string.h>

void SIM868_Call_Accept(ATTerminal* at) { ATTerminal_SendCommand(at, "ATA"); }

void SIM868_Call_Terminate(ATTerminal* at) { ATTerminal_SendCommand(at, "ATH"); }

void SIM868_Call_Place(ATTerminal* at, char* number)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "ATD%s;", number);
	ATTerminal_SendCommand(at, command);
}

char* SIM868_Call_ParseIndentification(char* info)
{
	char* rest  = info;
	char* token = strsep(&rest, ",");
	// Caller Number
	strsep(&token, "\"");
	return strsep(&token, "\"");
}
