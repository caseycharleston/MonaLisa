#include "client.h"
#include "rigid_transformation.h"
#include "kinematic_link.h"
#include "head.h"
#include <iostream>
#include <stdio.h>

using namespace std;
// Testing file for server. Make sure return values look right!
int main (int argc, char **argv) {
    // ** testing rotation of eyes as if its in the current unity environmetn
    Head h;
    // rotate to look at position of first grid
    h.rotateEyes(1.00, 0.34, 0.34); //first grid pos: (1.00, 0.34, 0.34)
    KinematicLink *rightEye = h.getDynamicRightEye();
    KinematicLink *leftEye = h.getDynamicLeftEye();

    cout << rightEye->getRotationQuaternions() << endl;
    cout << leftEye->getRotationQuaternions() << endl; // tgt: (0.00000, -0.10724, 0.09142, 0.99002)

    // rotate to look at position of second grid
    h.rotateEyes(1.00, 0.34, 0.11); //second grid pos: (1.00, 0.34, 0.11)
    cout << "look at 2nd grid\n" << rightEye->getRotationQuaternions() << endl;
    cout << leftEye->getRotationQuaternions() << endl; // tgt: (0.00000, -0.04956, 0.09268, 0.99446)


    // rotate to look at position of third grid
    h.rotateEyes(1.00, 0.34, -0.11);// third grid pos: (1.00, 0.34, -0.11)
    cout << "look at 3rd grid\n" << rightEye->getRotationQuaternions() << endl;
    cout << leftEye->getRotationQuaternions() << endl; // tgt: (0.00000, 0.00963, 0.09301, 0.99562)
    
    // RigidTransformation rt(0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    /*
    cout << "Starting test main @ test.cpp" << endl;
    Client myClient("Test");

    if (!myClient.ConnectToServer("127.0.0.1", 12345)) {
        cout << "Failed to connect to server. Exiting.";
        return 0;
    }

    // Basic send message tester
    // while (true) {
    //     char response;
    //     cout << "Send message? (y/n)";
    //     cin >> response;
    //     if (response == 'n') break;
    //     myClient.SendMessage("Hello World!");
    // }

    int count = 0;
    while (true) {
        char response;
        cout << "Send message? (y/n)";
        cin >> response;
        if (response == 'n') break;
        if (count % 2 == 0) {
            myClient.SendMessage("50,50,50,50,50,50");
        } else {
            myClient.SendMessage("-0.1,-0.1,-0.1,0.1,0.1,0.1");
        }
        count++;
    }
    */

    return 0;
}