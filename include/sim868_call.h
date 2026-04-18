#ifndef _SIM868_CALL_H_
#define _SIM868_CALL_H_

/**
 * \file
 * SIM868 Call management
 *
 * This file provides functions to manage the call connection of the SIM868 module, including accepting, terminating, and placing calls.
 * It also defines the necessary data structures and enumerations for handling call responses and statuses.
 */

#include "atterminal.h"

/**
 * Call AT response identifiers
 */
typedef enum _SIM868CallResponse_
{
	SIM868_CALL_READY          = 0xC2026E92, // Call Ready
	SIM868_CALL_RING           = 0xF54C2F6B, // RING
	SIM868_CALL_IDENTIFICATION = 0x9063C3FB, // CLIP
} SIM868CallResponse;

/**
 * Accept an incoming call.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_Call_Accept(ATTerminal* at);

/**
 * Terminate the current call.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_Call_Terminate(ATTerminal* at);

/**
 * Place a new call to the specified number.
 * \param at ATTerminal instance to send the command through
 * \param number Phone number to call
 */
void SIM868_Call_Place(ATTerminal* at, char* number);

/**
 * Parse the identification information from a response string.
 * \param info Response string containing the identification information
 * \return Parsed call identification information
 */
char* SIM868_Call_ParseIndentification(char* info);

#endif
