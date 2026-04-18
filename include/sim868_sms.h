#ifndef _SIM868_SMS_H_
#define _SIM868_SMS_H_

/**
 * \file
 * SIM868 SMS management
 *
 * This file provides functions to manage the SMS functionality of the SIM868 module, including sending SMS messages, requesting received messages, and deleting messages.
 * It also defines the necessary data structures and enumerations for handling SMS responses and parsing message information.
 */

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * SMS AT response identifiers
 */
typedef enum _SIM868SMSResponse_
{
	SIM868_SMS_READY    = 0xEE605F1D, // SMS Ready
	SIM868_SMS_SENT     = 0xC6536377, // CMGS
	SIM868_SMS_NEW_MSG  = 0x8789C36,  // CMTI
	SIM868_SMS_MSG_DATA = 0xC55361E4, // CMGR
} SIM868SMSResponse;

/**
 * SMS message information structure
 */
typedef struct _SIM868SMSMessageInfo_
{
	char*  Sender;
	size_t Length;
} SIM868SMSMessageInfo;

/**
 * Send an SMS message to the specified number with the given message content.
 * \param at ATTerminal instance to send the command through
 * \param number Recipient phone number as a string
 * \param msg Message content as a string
 */
void SIM868_SMS_Send(ATTerminal* at, char* number, char* msg);

/**
 * Request the content of a received SMS message by its index.
 * \param at ATTerminal instance to send the command through
 * \param index Index of the received message to request
 */
void SIM868_SMS_RequestReceivedMsg(ATTerminal* at, uint8_t index);

/**
 * Delete an SMS message by its index.
 * \param at ATTerminal instance to send the command through
 * \param index Index of the message to delete
 */
void SIM868_SMS_DeleteMsg(ATTerminal* at, uint8_t index);

/**
 * Parse the send message response to determine if the message was sent successfully.
 * \param info Response string containing the send message result
 * \return 1 if the message was sent successfully, 0 otherwise
 */
uint8_t SIM868_SMS_ParseSend(char* info);

/**
 * Parse the new message indication to extract the index of the received message.
 * \param info Response string containing the new message indication
 * \return Index of the received message
 */
uint8_t SIM868_SMS_ParseNewMsg(char* info);

/**
 * Parse the message information from a response string.
 * \param info Response string containing the message information
 * \return Parsed message information
 */
SIM868SMSMessageInfo SIM868_SMS_ParseMsgInfo(char* info);

/**
 * Read the content of a received SMS message into a buffer.
 * \param at ATTerminal instance to read the message from
 * \param data Buffer to store the message content
 * \param size Size of the buffer in bytes
 * \return Number of bytes read into the buffer
 */
size_t SIM868_SMS_ReadMsg(ATTerminal* at, void* data, size_t size);

#endif
