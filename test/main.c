/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Simple test for C.
 */

#include <udp.h>

#include <stdio.h>
#include <string.h>

typedef struct env {
  char           client[256];
  unsigned short port;
} Env;

void receiveMessage(UDPServer *server) {
  Env *env = server->env;

  server->buffer[server->bufsize] = 0;
  sprintf(env->client, "%s", inet_ntoa(server->addr_in.sin_addr));
  env->port = ntohs(server->addr_in.sin_port);
  printf("From %s(%hu): %s\n", (char*)server->env, env->port, server->buffer);
}

int main(int argc, char *argv[]) {
  Env        env = { "", 0 };
  int        client = 0;
  UDPServer *server = NULL;

  if (argc > 1) {
    if(!strcmp(argv[1], "-s")) {
      server = udpsopen(8008, stdout, stderr);
    } else if (!strcmp(argv[1], "-c")) {
      server = udpiopen(8008, 8009, stdout, stderr);
      client = 1;
    }
  }
  
  if (server) {
    server->env = &env;
    udplisten(server, receiveMessage);
    printf("Send 'q' to quit.\n");
    while (1) {
      const size_t size = 1024;
      char         line[size];
      char        *lineptr = line;

      getline((char**)&lineptr, (size_t*)&size, stdin);
      if (strcmp(line, "q\n")) {
        if (strcmp(env.client, "") || client) {
          if (!client) {
            inet_aton(env.client, &server->addr_out.sin_addr);
            server->addr_out.sin_port = htons(env.port);
          }
          // -1 because don't send newline char
          udpsend(server, (unsigned char*)line, strlen(line) - 1);
        } else {
          fprintf(stderr, "Cannot send a message because no client has sent anything yet.\n");
        }
      } else break;
    }
    udpclose(server);
  } else {
    printf("Run '%s -c' for a client, and '%s -s' for a server\n", argv[0], argv[0]);
  }
  return 0;
}