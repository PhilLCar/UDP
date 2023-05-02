/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Common structures for C.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>

#define UDP_MAX_CHUNK (1 << 16)
#define UDP_TIMEOUT        3000

extern const struct timeval TIMEOUT;

/*
NOTE:
This isn't made to be thread safe for multiple sending threads. If multiple
threads are going to send messages, they should make sure between themselves
that none are sending simultaneously.
*/

typedef struct udp_server {
  FILE               *messages;
  FILE               *errors;
  int                 fd;
  unsigned char       buffer[UDP_MAX_CHUNK];
  int                 bufsize;
  struct sockaddr_in  addr_in;
  struct sockaddr_in  addr_out;
  pthread_t           thread;
  void              (*callback)(struct udp_server*);
  void               *env;
} UDPServer;

typedef void (*UDPCallback)(UDPServer *server);

#ifdef __cplusplus
extern "C" {
#endif

void udplisten(UDPServer *server, UDPCallback callback);
void udpstop(UDPServer *server);

int udpsend(UDPServer *server, const unsigned char *bytes, size_t length);

void udpclose(UDPServer *server);

#ifdef __cplusplus
}
#endif

#endif