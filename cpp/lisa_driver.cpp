#include "client.h"
#include "rigid_transformation.h"
// #include "optimize.cpp"
#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

bool debug = true;
Client myClient("LisaDriver");

// Testing file for server. Make sure return values look right!
int main () {
    if (debug) cout << "Starting lisa_driver main @ lisa_driver.cpp" << endl;
    

    if (!myClient.ConnectToServer("127.0.0.1", 12345)) {
        cout << "Failed to connect to server. Exiting.";
        return 0;
    }
    // RIGID TRANSFORM OBJECT
    float headDist = 1.0;
    RigidTransformation leftEye(0.13 + -headDist, -0.015, -0.076, 0, 0, 0);
    RigidTransformation rightEye(0.13 + -headDist, -0.015, 0.076, 0, 0, 0);
    
    return 0;
}

// Package send an array of 6 floats (first 3 are rot coords for the left eye, second 3 are rot coords for the right eye)
void pckg_send_coords(float eye1[], float eye2[]) {
    // concatenate values to conform to the expected message format in Unity Controller.cs
    string msg = to_string(eye1[0]) + "," + to_string(eye1[1]) + "," + to_string(eye1[2]) + "," +
                 to_string(eye2[0]) + "," + to_string(eye2[1]) + "," + to_string(eye2[2]);
    myClient.SendMessage(msg);
}