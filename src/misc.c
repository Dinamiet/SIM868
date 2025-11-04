#include "sim868_misc.h"

#include <stdio.h>

#define MAX_COMMAND_SIZE 16

void SIM868_Misc_CommandEcho(ATTerminal* at, bool echoEnabled)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "ATE%d", echoEnabled);
	ATTerminal_SendCommand(at, command);
}

void SIM868_Misc_Check(ATTerminal* at)
{
	ATTerminal_SendCommand(at, "AT");
}
