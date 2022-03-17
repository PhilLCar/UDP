/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP client for C.
 */

#include <udpclient.h>

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int _udpopen(struct sockaddr_in *addr, FILE *messages, FILE *errors) {
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if(socket_fd < 0){
    fprintf(errors, "Couldn't create socket!\n");
    return socket_fd;
  }
  fprintf(messages, "Socket created successfully.\n");

  if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &TIMEOUT, sizeof(struct timeval)) < 0) {
    fprintf(errors, "Couldn't set timeout!\n");
  }
  
  if(bind(socket_fd, (struct sockaddr*)addr, sizeof(struct sockaddr_in)) < 0){
    fprintf(errors, "Bind failed!\n");
    close(socket_fd);
    return -1;;
  }
  fprintf(messages, "Binded successfully.\n");

  return socket_fd;
}


UDPServer *udpcopen(const char *address, const unsigned short port, FILE *messages, FILE *errors) {
  struct sockaddr_in  iaddr;
  struct sockaddr_in  oaddr;
  int                 socket_fd;
  UDPServer          *server = NULL;


  oaddr.sin_family      = AF_INET;
  oaddr.sin_port        = htons(port);
  oaddr.sin_addr.s_addr = inet_addr(address);

  iaddr.sin_family      = AF_INET;
  iaddr.sin_port        = htons(port);
  iaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if ((socket_fd = _udpopen(&iaddr, messages, errors))) {
    server           = malloc(sizeof(UDPServer));
    server->messages = messages;
    server->errors   = errors;
    server->fd       = socket_fd;
    server->addr_out = oaddr;
    server->addr_in  = iaddr;
    server->callback = NULL;
  }
  return server;
}

UDPServer *udpiopen(const unsigned short oport, const unsigned short iport, FILE *messages, FILE *errors) {
  struct sockaddr_in  iaddr;
  struct sockaddr_in  oaddr;
  int                 socket_fd;
  UDPServer          *server = NULL;


  oaddr.sin_family      = AF_INET;
  oaddr.sin_port        = htons(oport);
  oaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  iaddr.sin_family      = AF_INET;
  iaddr.sin_port        = htons(iport);
  iaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if ((socket_fd = _udpopen(&iaddr, messages, errors))) {
    server           = malloc(sizeof(UDPServer));
    server->messages = messages;
    server->errors   = errors;
    server->fd       = socket_fd;
    server->addr_out = oaddr;
    server->addr_in  = iaddr;
    server->callback = NULL;
  }
  return server;
}