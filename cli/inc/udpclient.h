/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP client for C.
 */

#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

UDPServer *udpcopen(const char *address, const unsigned short port, FILE *messages, FILE *errors);
UDPServer *udpiopen(const unsigned short oport, const unsigned short iport, FILE *message, FILE *errors);

#ifdef __cplusplus
}
#endif

#endif