#include "client.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

SocketClient::SocketClient(std::string name) : sockfd(-1), name(name) {}

bool SocketClient::connectToServer() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(10000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server." << std::endl;
        close(sockfd);
        return false;
    }

    send_message(name.c_str());

    return true;
}

void SocketClient::send_message(const char* message) {
    if (sockfd != -1) {
        int msgLen = strlen(message);
        send(sockfd, message, msgLen, 0);
        send(sockfd, "\0", 1, 0);
    }
}

std::string SocketClient::receive_message() {
    std::string message;
   
    if (sockfd != -1) {
        char buffer[4096];
        int bytesRead = 0;
        while (true) {
            bytesRead = recv(sockfd, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) {
                break;
            }

            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\0') {
                    return message;
                }
                message += buffer[i];
            }
        }
    }
    
    return message;
}

void SocketClient::closeConnection() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
}

SocketClient::~SocketClient() {
    closeConnection();
}
