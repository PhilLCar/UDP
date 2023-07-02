/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Common structures for C.
 */

#include <udpcommon.h>

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

const struct timeval TIMEOUT = { UDP_TIMEOUT / 1000, (UDP_TIMEOUT % 1000) * 1000 };

void *_udplisten(void *vargp) {
  socklen_t  addr_size = sizeof(struct sockaddr_in);
  UDPServer *server    = (UDPServer*)vargp;

  while (server->callback) {
    int n = recvfrom(server->fd, server->buffer, UDP_MAX_CHUNK, 0, (struct sockaddr*)&server->addr_in, &addr_size);
    if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
      fprintf(server->errors, "Couldn't receive\n");
      server->callback = NULL;
    } else if (n > 0 && server->callback) {
      server->bufsize = n;
      server->callback(server);
    }
  }

  return NULL;
}

void udplisten(UDPServer *server, UDPCallback callback) {
  server->callback = callback;
  pthread_create(&server->thread, NULL, _udplisten, server);
}

void udpstop(UDPServer *server) {
  server->callback = NULL;
  pthread_join(server->thread, NULL);
}

int udpsend(UDPServer *server, const unsigned char *bytes, size_t length) {
  return sendto(server->fd, bytes, length, 0, (struct sockaddr*)&server->addr_out, sizeof(struct sockaddr_in)) >= 0;
}

void udpclose(UDPServer *server) {
  if (server->callback) udpstop(server);
  close(server->fd);
  free(server);
}