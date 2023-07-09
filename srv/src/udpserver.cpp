/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP server for C++.
 */

#include <udpserver.hpp>
#include <udpserver.h>

#include <cstring>

namespace UDP
{
  Server::Server(const unsigned short port, const void* env)
    : Common(port, env)
  {
    server = udpopen(port, messages, errors);
    server->env = this;
  }

  bool Server::send(const IPV4Address& client, const unsigned char* bytes, size_t length) {
    server->addr_out.sin_addr.s_addr = htonl(client.address_int());
    server->addr_out.sin_port        = htons(client.port());
    return udpsend(server, bytes, length) == (int)length;
  }

  bool Server::send(const IPV4Address& client, const std::string& message) {
    int length = message.length();
    server->addr_out.sin_addr.s_addr = htonl(client.address_int());
    server->addr_out.sin_port        = htons(client.port());
    return udpsend(server, (unsigned char*)message.c_str(), length) == length;
  }

  bool Server::send (const IPV4Address& client, const char* message) {
    int length = std::strlen(message);
    server->addr_out.sin_addr.s_addr = htonl(client.address_int());
    server->addr_out.sin_port        = htons(client.port());
    return udpsend(server, (unsigned char*)message, length) == length;
  }
}
