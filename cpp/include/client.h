#ifndef CPPCLIENT_H
#define CPPCLIENT_H

#include <string>
#include <boost/asio.hpp>

class Client {
public:
    Client(const std::string& name);
    bool ConnectToServer(const std::string& serverIP, int serverPort);
    bool SendMessage(const std::string& message);
    std::string ReceiveMessage();

private:
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket clientSocket;
    std::string clientName;
};

#endif
