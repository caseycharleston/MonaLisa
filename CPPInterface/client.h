#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <string>

class SocketClient {
private:
    int sockfd;
    std::string name;

public:
    SocketClient(std::string name);
    bool connectToServer();
    void send_message(const char* message);
    std::string receive_message();
    void closeConnection();
    ~SocketClient();
};

#endif