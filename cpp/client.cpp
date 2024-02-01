#include "client.h"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

Client::Client(const std::string& name) : clientSocket(ioService), clientName(name) {}

bool Client::ConnectToServer(const std::string& serverIP, int serverPort) {
    tcp::resolver resolver(ioService);
    tcp::resolver::query query(serverIP, std::to_string(serverPort));

    try {
        boost::asio::connect(clientSocket, resolver.resolve(query));
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to the server: " << e.what() << std::endl;
        return false;
    }

    // Send the client's name to the server
    sendMessage(clientName);

    return true;
}

bool Client::sendMessage(const std::string& message) {
    try {
        boost::asio::write(clientSocket, boost::asio::buffer(message + '\n'));
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message: " << e.what() << std::endl;
        return false;
    }
    return true;
}

std::string Client::receiveMessage() {
    boost::asio::streambuf response;
    try {
        boost::asio::read_until(clientSocket, response, '\n');
    } catch (const std::exception& e) {
        std::cerr << "Failed to receive message: " << e.what() << std::endl;
        return "";
    }

    std::string message = boost::asio::buffer_cast<const char*>(response.data());
    return message;
}
