#ifndef _SIM868_GSM_H_
#define _SIM868_GSM_H_

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum _SIM868GSMResponse_
{
	SIM868_GSM_FUNC           = 0x3C05AEFF, // CFUN
	SIM868_GSM_PIN            = 0x754EDBE9, // CPIN
	SIM868_GSM_NETWORKCHANGE  = 0xC8DDE4F3, // CREG
	SIM868_GSM_SIGNAL_QUALITY = 0x78219D86, // CSQ
} SIM868GSMResponse;

typedef enum _SIM868GSMFunctionality_
{
	SIM868_GSM_FUNC_MINIMUM = 0,
	SIM868_GSM_FUNC_FULL    = 1,
	SIM868_GSM_FUNC_NO_RF   = 4,
} SIM868GSMFunctionality;

typedef enum _SIM868GSMNetworkNotify_
{
	SIM868_GSM_NETWORK_NOTIFY_NO,
	SIM868_GSM_NETWORK_NOTIFY_REGISTRATION,
	SIM868_GSM_NETWORK_NOTIFY_LOCATION,
} SIM868GSMNetworkNotify;

typedef enum _SIM868NetworkStat_
{
	SIM868_GSM_NETWORK_STATUS_NOT_REGISTERED,
	SIM868_GSM_NETWORK_STATUS_REGISTERED,
	SIM868_GSM_NETWORK_STATUS_SEARCHING,
	SIM868_GSM_NETWORK_STATUS_DENIED,
	SIM868_GSM_NETWORK_STATUS_UNKNOWN,
	SIM868_GSM_NETWORK_STATUS_ROAMING,
} SIM868GSMNetworkStat;

typedef struct _SIM868GSMNetworkInfo_
{
	SIM868GSMNetworkStat Status;
	uint16_t             LocationCode;
	uint16_t             CellID;
} SIM868GSMNetworkInfo;

typedef struct _SIM868GSMSignalInfo_
{
	uint8_t RSSI;
	uint8_t BER;
} SIM868GSMSignalInfo;

void SIM868_GSM_Functionality(ATTerminal* at, SIM868GSMFunctionality func);
void SIM868_GSM_EnterPin(ATTerminal* at, char* pin);
void SIM868_GSM_SignalCheck(ATTerminal* at);
void SIM868_GSM_NetworkRegistrationStatus(ATTerminal* at, SIM868GSMNetworkNotify notify);
void SIM868_GSM_SetAPN(ATTerminal* at, char* apn, char* user, char* pwd);
void SIM868_GSM_ConnectData(ATTerminal* at);
void SIM868_GSM_IPAddress(ATTerminal* at);

SIM868GSMNetworkInfo SIM868_GSM_ParseNetworkInfo(char* info);
SIM868GSMSignalInfo  SIM868_GSM_ParseSignalInfo(char* info);

#endif
