#ifndef _SIM868_HTTP_H_
#define _SIM868_HTTP_H_

/**
 * \file
 * SIM868 HTTP management
 *
 * This file provides functions to manage the HTTP functionality of the SIM868 module, including starting and terminating HTTP sessions, making HTTP POST requests, and retrieving HTTP response data.
 * It also defines the necessary data structures and enumerations for handling HTTP responses and parsing action information and response data.
 */

#include "atterminal.h"

#include <stdint.h>

/**
 * HTTP AT response identifiers
 */
typedef enum _SIM868HTTPResponse_
{
	SIM868_HTTP_RESPONSE_ACTION_STATUS = 0x6244591F, // HTTPACTION
	SIM868_HTTP_RESPONSE_RESPONSE_DATA = 0xA8048965, // HTTPREAD
} SIM868HTTPResponse;

/**
 * HTTP action types
 */
typedef enum _SIM868HTTPAction_
{
	SIM868_HTTP_ACTION_GET,
	SIM868_HTTP_ACTION_POST,
	SIM868_HTTP_ACTION_HEAD,
	SIM868_HTTP_ACTION_DELETE
} SIM868HTTPAction;

/**
 * HTTP action information structure
 */
typedef struct _SIM868HTTPActionInfo_
{
	SIM868HTTPAction Action;
	uint16_t         Status;
	size_t           ResponseLength;
} SIM868HTTPActionInfo;

/**
 * Start an HTTP session with the specified bearer identifier.
 * \param at ATTerminal instance to send the command through
 * \param identifier Bearer identifier number to use for the HTTP session
 * Note: The bearer connection must be established before starting the HTTP session.
 */
void SIM868_HTTP_StartSession(ATTerminal* at, uint8_t identifier);

/**
 * Make an HTTP POST request to the specified URL with the given data and size.
 * \param at ATTerminal instance to send the command through
 * \param url URL to send the POST request to
 * \param data Pointer to the data to be sent in the POST request
 * \param size Size of the data to be sent in bytes
 */
void SIM868_HTTP_Post(ATTerminal* at, char* url, void* data, size_t size);

/**
 * Request the HTTP response data after an HTTP action has been performed.
 * \param at ATTerminal instance to send the command through
 * Note: This function should be called after receiving an HTTPACTION response to retrieve the response data
 */
void SIM868_HTTP_RequestResponseData(ATTerminal* at);

/**
 * Terminate the current HTTP session.
 * \param at ATTerminal instance to send the command through
 * Note: This will close the HTTP session and release any resources associated with it. A new session must be started to perform further HTTP actions.
 */
void SIM868_HTTP_TerminateSession(ATTerminal* at);

/**
 * Parse the HTTP action information from a response string.
 * \param info Response string containing the HTTP action information
 * \return Parsed HTTP action information
 */
SIM868HTTPActionInfo SIM868_HTTP_ParseActionInfo(char* info);

/**
 * Parse the length of the HTTP response data from a response string.
 * \param info Response string containing the HTTP response data
 * \return Length of the HTTP response data in bytes
 */
size_t SIM868_HTTP_ParseReadData(char* info);

/**
 * Read the HTTP response data into a buffer.
 * \param at ATTerminal instance to read the data from
 * \param data Pointer to the buffer where the response data will be stored
 * \param size Size of the buffer in bytes
 * \return Number of bytes read into the buffer
 */
size_t SIM868_HTTP_ReadData(ATTerminal* at, void* data, size_t size);

#endif
