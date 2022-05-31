/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP server for C.
 */

#include <udpserver.h>

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

UDPServer *udpopen(const unsigned short port, FILE *messages, FILE *errors) {
  struct sockaddr_in  addr;
  int                 socket_fd;
  UDPServer          *server = NULL;
  
  socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
  if(socket_fd < 0){
    fprintf(errors, "Couldn't create socket!\n");
    return server;
  }
  fprintf(messages, "Socket created successfully.\n");
  
  addr.sin_family      = AF_INET;
  addr.sin_port        = htons(port);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &TIMEOUT, sizeof(struct timeval)) < 0) {
    fprintf(errors, "Couldn't set timeout!\n");
  }
  
  if(bind(socket_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0){
    fprintf(errors, "Bind failed!\n");
    close(socket_fd);
    return server;
  }
  fprintf(messages, "Binded successfully.\n");
  
  server           = malloc(sizeof(UDPServer));
  server->messages = messages;
  server->errors   = errors;
  server->fd       = socket_fd;
  server->callback = NULL;
  
  return server;
}