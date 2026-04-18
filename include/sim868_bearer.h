#ifndef _SIM868_BEARER_H_
#define _SIM868_BEARER_H_

/**
 * \file
 * SIM868 Bearer management
 *
 * This file provides functions to manage the bearer connection of the SIM868 module, including opening, closing, and querying the status of the connection.
 * It also defines the necessary data structures and enumerations for handling bearer responses and statuses.
 */

#include "atterminal.h"

#include <stdint.h>

/**
 * Bearer AT response identifiers
 */
typedef enum _SIM868BearerResponse_
{
	SIM868_BEARER_RESPONSE_STATUS = 0xCF17F5DB, // SAPBR
} SIM868BearerResponse;

/**
 * Bearer connection types
 */
typedef enum _SIM868BearerConnection_
{
	SIM868_BEARER_CONNECTION_CSD,
	SIM868_BEARER_CONNECTION_GPRS
} SIM868BearerConnection;

/**
 * Bearer status types
 */
typedef enum _SIM868BearerStatus_
{
	SIM868_BEARER_STATUS_CONNECTING,
	SIM868_BEARER_STATUS_CONNECTED,
	SIM868_BEARER_STATUS_CLOSING,
	SIM868_BEARER_STATUS_CLOSED
} SIM868BearerStatus;

/**
 * Bearer status information
 */
typedef struct _SIM868BearerStatusInfo_
{
	uint8_t            Identifier;    /** Bearer identifier number */
	SIM868BearerStatus Status;        /** Bearer status */
	char               IPAddress[16]; /** Bearer IP address */
} SIM868BearerStatusInfo;

/**
 * Open a specified bearer connection with the given APN and connection type.
 * \param at ATTerminal instance to send the command through
 * \param identifier Bearer identifier number
 * \param apn Access Point Name for the connection
 * \param type Type of the bearer connection
 */
void SIM868_Bearer_OpenConnection(ATTerminal* at, uint8_t identifier, char* apn, SIM868BearerConnection type);

/**
 * Close a specified bearer connection.
 * \param at ATTerminal instance to send the command through
 * \param identifier Bearer identifier number
 */
void SIM868_Bearer_CloseConnection(ATTerminal* at, uint8_t identifier);

/**
 * Query the status of a specified bearer connection.
 * \param at ATTerminal instance to send the command through
 * \param identifier Bearer identifier number
 */
void SIM868_Bearer_QueryConnection(ATTerminal* at, uint8_t identifier);

/**
 * Parse the status information from a response string.
 * \param info Response string containing the status information
 * \return Parsed bearer status information
 */
SIM868BearerStatusInfo SIM868_Bearer_ParseStatus(char* info);

#endif
