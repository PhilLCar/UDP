/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Common structures for C++.
 */

#ifndef UDPCOMMON_HPP
#define UDPCOMMON_HPP

#include <udpcommon.h>
#include <IPV4Address.hpp>

#include <vector>
#include <algorithm>
#include <string>

using namespace Networking;

namespace UDP {
  struct Message {
    unsigned char* bytes;
    size_t         size;
    IPV4Address    address;
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