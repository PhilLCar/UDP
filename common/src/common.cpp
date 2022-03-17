/* Author: Philippe Caron (philippe-caron@hotmail.com)
 * Date: 16 Mar 2022
 * Description: Very simple UDP server for C++.
 */

#include <common.hpp>

#include <fstream>


namespace std {
  string to_string(UDP::IPV4Address address) {
    string str = "";
    str = to_string(address.bytes[0]) + "." +
          to_string(address.bytes[1]) + "." +
          to_string(address.bytes[2]) + "." +
          to_string(address.bytes[3]) + ":" +
          to_string(address.port);
    return str;
  }
}

namespace UDP
{
  IPV4Address::IPV4Address(const char *address) {
    std::string current = "";
    int b = 4;
    for (int i = 0; address[i]; i++) {
      char c = address[i];
      if (c != '.' && c != ':') {
        current += c;
      } else {
        bytes[--b] = std::stoi(current);
        current = "";
      }
    }
    port = std::stoi(current);
  }

  Common::Common(const unsigned short port, const void* env)
    : port(port)
    , env(env)
    , mname(".messages." + std::to_string(port) + ".tmp")
    , ename(".errors."   + std::to_string(port) + ".tmp")
    , lastMessage("")
    , lastError("")
  {
    messages = std::fopen(mname.c_str(), "w+");
    errors   = std::fopen(ename.c_str(), "w+");
  }

  Common::~Common() {
    udpclose(server);
    std::fclose(messages);
    std::fclose(errors);
    std::remove(mname.c_str());
    std::remove(ename.c_str());
  }

  void Common::start() {
    udplisten(server, receive);
  }

  void Common::stop() {
    udpstop(server);
  }

  const std::string& Common::message() {
    std::fflush(messages);
    {
      std::ifstream mfile(mname, std::ios_base::in);
      std::string   m;

      while (std::getline(mfile, m)) lastMessage = m;
      mfile.close();
    }
    return lastMessage;
  }

  const std::string& Common::error() {
    std::fflush(errors);
    {
      std::ifstream mfile(mname, std::ios_base::in);
      std::string   m;

      while (std::getline(mfile, lastMessage)) lastError = m;
      mfile.close();
    }
    return lastMessage;
  }

  void Common::receive(UDPServer *server) {
    Message message;
    Common* this_com = (Common*)server->env;


    message.bytes   = server->buffer;
    message.size    = server->bufsize;
    message.address = inet_ntoa(server->addr_in.sin_addr);
    message.port    = ntohs(server->addr_in.sin_port);

    this_com->onReceive.trigger(message, this_com->env);
  }
}