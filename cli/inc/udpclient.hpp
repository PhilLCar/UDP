/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP client for C++.
 */

#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <udpcommon.hpp>

#include <string>

using namespace Networking;

namespace UDP {
  class Client : public Common {
  public:
    inline Client(const IPV4Address server, const IPV4Address client)
      : Client(server.port(), client.port(), server.address_str().c_str(), nullptr)
    {}
    inline Client(const unsigned short port, const char* address)
      : Client(port, port, address, nullptr)
    {}
    inline Client(const unsigned short oport, const unsigned short iport)
      : Client(oport, iport, "127.0.0.1", nullptr)
    {}

    template <typename T>
    inline Client(const IPV4Address server, const IPV4Address client, T& env)
      : Client(server.port(), client.port(), server.address_str().c_str(), (const void*)&env)
    {}
    template <typename T>
    inline Client(const unsigned short port, const char* address, const T& env)
      : Client(port, port, address, (const void*)&env)
    {}
    template <typename T>
    inline Client(const unsigned short oport, const unsigned short iport, const T& env)
      : Client(oport, iport, "127.0.0.1", (const void*)&env)
    {}

    ~Client();

  private:
    explicit Client(const unsigned short oport, const unsigned short iport, const char* iaddress, const void* env);

  public:
    bool send(const unsigned char* bytes, size_t length);
    bool send(const std::string& message);
    bool send(const char* message);

    template <typename T>
    inline bool send(const T& serialized) {
      return send((unsigned char*)&serialized, sizeof(T));
    }
  };
}

#endif