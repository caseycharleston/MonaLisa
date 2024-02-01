#ifndef CPPCLIENT_H
#define CPPCLIENT_H

#include <string>
#include <boost/asio.hpp>

class Client {
public:
    Client(const std::string& name);
    bool ConnectToServer(const std::string& serverIP, int serverPort);
    bool sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket clientSocket;
    std::string clientName;
};

#endif
