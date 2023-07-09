/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP client for C++.
 */

#include <udpclient.hpp>
#include <udpclient.h>

#include <cstring>

namespace UDP
{
  Client::Client(const unsigned short oport, const unsigned short iport,  const char* iaddress, const void* env)
    : Common(oport, env)
  {
    if (oport == iport) {
      // Remote connection
      server = udpcopen(iaddress, iport, messages, errors);
    } else {
      // Local connection
      server = udpiopen(oport, iport, messages, errors);
    }
    server->env = this;
  }

  bool Client::send(const unsigned char* bytes, size_t length) {
    return udpsend(server, bytes, length) == (int)length;
  }

  bool Client::send(const std::string& message) {
    int length = message.length();
    return udpsend(server, (unsigned char*)message.c_str(), length) == length;
  }

  bool Client::send (const char* message) {
    int length = std::strlen(message);
    return udpsend(server, (unsigned char*)message, length) == length;
  }
}
