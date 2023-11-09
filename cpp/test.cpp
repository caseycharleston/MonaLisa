#include "client.h"
#include <iostream>
#include <stdio.h>

using namespace std;
// Testing file for server. Make sure return values look right!
int main () {
    cout << "Starting test main @ test.cpp" << endl;
    Client myClient("Test");

    if (!myClient.ConnectToServer("127.0.0.1", 12345)) {
        cout << "Failed to connect to server. Exiting.";
        return 0;
    }

    /* Basic send message tester */
    // while (true) {
    //     char response;
    //     cout << "Send message? (y/n)";
    //     cin >> response;
    //     if (response == 'n') break;
    //     myClient.SendMessage("Hello World!");
    // }

    /* Basic send rotational values tester */

   
    while (true) {
        char response;
        cout << "Send message? (y/n)";
        cin >> response;
        if (response == 'n') break;
        myClient.SendMessage("1,1,1,1,1,-1");
    }
    return 0;
}