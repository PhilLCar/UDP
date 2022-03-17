/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP server for C.
 */

#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

UDPServer *udpsopen(const unsigned short port, FILE *messages, FILE *errors);

#ifdef __cplusplus
}
#endif

#endif