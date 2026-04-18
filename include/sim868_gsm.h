#ifndef _SIM868_GSM_H_
#define _SIM868_GSM_H_

/**
 * \file
 * SIM868 GSM management
 *
 * This file provides functions to manage the GSM functionality of the SIM868 module, including setting the functionality level, entering the SIM PIN, checking signal quality, and managing network
 * registration status. It also defines the necessary data structures and enumerations for handling GSM responses and parsing network and signal information.
 */

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * GSM AT response identifiers
 */
typedef enum _SIM868GSMResponse_
{
	SIM868_GSM_FUNC           = 0x3C05AEFF, // CFUN
	SIM868_GSM_PIN            = 0x754EDBE9, // CPIN
	SIM868_GSM_NETWORKCHANGE  = 0xC8DDE4F3, // CREG
	SIM868_GSM_SIGNAL_QUALITY = 0x78219D86, // CSQ
} SIM868GSMResponse;

/**
 * GSM functionality levels
 */
typedef enum _SIM868GSMFunctionality_
{
	SIM868_GSM_FUNC_MINIMUM = 0,
	SIM868_GSM_FUNC_FULL    = 1,
	SIM868_GSM_FUNC_NO_RF   = 4,
} SIM868GSMFunctionality;

/**
 * GSM network registration notification types
 */
typedef enum _SIM868GSMNetworkNotify_
{
	SIM868_GSM_NETWORK_NOTIFY_NO,
	SIM868_GSM_NETWORK_NOTIFY_REGISTRATION,
	SIM868_GSM_NETWORK_NOTIFY_LOCATION,
} SIM868GSMNetworkNotify;

/**
 * GSM network registration status types
 */
typedef enum _SIM868NetworkStat_
{
	SIM868_GSM_NETWORK_STATUS_NOT_REGISTERED,
	SIM868_GSM_NETWORK_STATUS_REGISTERED,
	SIM868_GSM_NETWORK_STATUS_SEARCHING,
	SIM868_GSM_NETWORK_STATUS_DENIED,
	SIM868_GSM_NETWORK_STATUS_UNKNOWN,
	SIM868_GSM_NETWORK_STATUS_ROAMING,
} SIM868GSMNetworkStat;

/**
 * GSM network information structure
 */
typedef struct _SIM868GSMNetworkInfo_
{
	SIM868GSMNetworkStat Status;
	uint16_t             LocationCode;
	uint16_t             CellID;
} SIM868GSMNetworkInfo;

/**
 * GSM signal information structure
 */
typedef struct _SIM868GSMSignalInfo_
{
	uint8_t RSSI;
	uint8_t BER;
} SIM868GSMSignalInfo;

/**
 * Set the GSM functionality level of the SIM868 module.
 * \param at ATTerminal instance to send the command through
 * \param func Desired GSM functionality level
 */
void SIM868_GSM_Functionality(ATTerminal* at, SIM868GSMFunctionality func);

/**
 * Enter the SIM PIN code to unlock the GSM functionality.
 * \param at ATTerminal instance to send the command through
 * \param pin SIM PIN code as a string
 */
void SIM868_GSM_EnterPin(ATTerminal* at, char* pin);

/**
 * Check the GSM signal quality and retrieve the RSSI and BER values.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_GSM_SignalCheck(ATTerminal* at);

/**
 * Set the network registration status notification type to receive updates on network registration changes.
 * \param at ATTerminal instance to send the command through
 * \param notify Desired network registration notification type
 */
void SIM868_GSM_NetworkRegistrationStatus(ATTerminal* at, SIM868GSMNetworkNotify notify);

/**
 * Parse the GSM network information from a response string.
 * \param info Response string containing the network information
 * \return Parsed GSM network information
 */
SIM868GSMNetworkInfo SIM868_GSM_ParseNetworkInfo(char* info);

/**
 * Parse the GSM signal information from a response string.
 * \param info Response string containing the signal information
 * \return Parsed GSM signal information
 */
SIM868GSMSignalInfo SIM868_GSM_ParseSignalInfo(char* info);

#endif
