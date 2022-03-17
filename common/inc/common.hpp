/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Common structures for C++.
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <common.h>

#include <vector>
#include <algorithm>
#include <string>

namespace UDP {
  class IPV4Address;
}

namespace std {
  string to_string(UDP::IPV4Address address);
}

namespace UDP {
  struct IPV4Address {
  public:
    IPV4Address(const char *address);
    inline IPV4Address(const unsigned int address, const unsigned short port)
      : address(address)
      , port(port)
    {}
    inline IPV4Address(const std::string& address)
      : IPV4Address(address.c_str())
    {}
  public:
    friend std::string std::to_string(IPV4Address address);
  public:
    union {
      unsigned char bytes[4];
      unsigned int  address;
    };
    unsigned short port;
  };

  struct Message {
    unsigned char* bytes;
    size_t         size;
    std::string    address;
    unsigned short port;
  };

  typedef void (*Callback)(Message&, void*);

  class ReceptionEvent {
    friend class Common;

  public:
    inline void operator +=(Callback callback) {
      callbacks.push_back(callback);
    }
    inline void operator -=(Callback callback) {
      callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), callback), callbacks.end());
    }
  private:
    inline void trigger(Message& message, const void *env) {
      for (auto callback : callbacks) callback(message, (void*)env);
    }
  private:
    std::vector<Callback> callbacks;
  };

  class Common {
  protected:
    explicit Common(const unsigned short port, const void *env);

  public:
    ~Common();

  public:
    void start();
    void stop();

    const std::string& message();
    const std::string& error();

  private:
    static void receive(UDPServer* server);

  public:
    ReceptionEvent onReceive;

  protected:
    const unsigned short port;
    const void*          env;

    UDPServer*  server;
    std::string mname;
    std::string ename;
    std::string lastMessage;
    std::string lastError;
    std::FILE*  messages;
    std::FILE*  errors;
  };
}

#endif