#include "client.h"
#include "rigid_transformation.h"
// #include "optimize.cpp"
#include <iostream>
#include <cstdio>
#include <string.h>
#include <math.h>

using namespace std;

bool debug = true;
Client myClient("LisaDriver");

// Package send an array of 6 floats (first 3 are rot coords for the left eye, second 3 are rot coords for the right eye)
void pckg_send_coords(float eye1[], float eye2[]) {
    // concatenate values to conform to the expected message format in Unity Controller.cs
    string msg = to_string(eye1[0]) + "," + to_string(eye1[1]) + "," + to_string(eye1[2]) + "," + to_string(eye1[3]) + ","
                + to_string(eye2[0]) + "," + to_string(eye2[1]) + "," + to_string(eye2[2]) + "," + to_string(eye2[3]);
    myClient.SendMessage(msg);
}

// Necessary because Unity rotations are done in degrees while it is done in radians in C++
void RadiansToDegrees(float arr[]) {
        arr[0] = arr[0] * 180 / M_PI;
        arr[1] = arr[1] * 180 / M_PI;
        arr[2] = arr[2] * 180 / M_PI;
}

// Testing file for server. Make sure return values look right!
int main () {
    if (debug) cout << "Starting lisa_driver main @ lisa_driver.cpp" << endl;
    if (!myClient.ConnectToServer("127.0.0.1", 12345)) {
        cout << "Failed to connect to server. Exiting.";
        return 0;
    }

    // RIGID TRANSFORM OBJECT
    float headDist = 1.0;
    RigidTransformation leftEye(0.13 + -headDist, -0.015, -0.076, 0, 0, 0, 1);
    RigidTransformation rightEye(0.13 + -headDist, -0.015, 0.076, 0, 0, 0, 1);

    /*
        Plug in values here of target position
    */
    Eigen::Quaternionf leftEyeRT = leftEye.computeRotationTransformation(1, 0.1125, 0.3375);
    Eigen::Quaternionf rightEyeRT = rightEye.computeRotationTransformation(1, 0.1125, 0.3375);

    // A
    // Eigen::Quaternionf leftEyeRT = leftEye.computeRotationTransformation(1, 0.3375, 0.3375);
    // Eigen::Quaternionf rightEyeRT = rightEye.computeRotationTransformation(1, 0.3375, 0.3375);

    Eigen::Vector4f lCoeffs = leftEyeRT.coeffs();
    Eigen::Vector4f rCoeffs = rightEyeRT.coeffs();
    if (debug) {
    // Displaying the results
        std::cout << "Left Eye" << endl;
        std::cout << "Quaternion: " << lCoeffs.transpose() << std::endl;
        std::cout << "Right Eye" << endl;
        std::cout << "Quaternion: " << rCoeffs.transpose() << std::endl;
    }

    char answer = 'n';
    cout << "type 'y' to continue" << endl;
    while (answer != 'y')
        cin >> answer;
    
    // w, x, y, z
    float lEyeMsg[] = {lCoeffs(0), lCoeffs(1), lCoeffs(2), lCoeffs(3)};
    float rEyeMsg[] = {rCoeffs(0), rCoeffs(1), rCoeffs(2), rCoeffs(3)};

    // RadiansToDegrees(lEyeMsg);
    // RadiansToDegrees(rEyeMsg);
    if (debug) {
        cout << "Values to send: " << endl;
        cout << "Left eye: " << lEyeMsg[0] << " " << lEyeMsg[1] << " " << lEyeMsg[2] << " " << lEyeMsg[3] << endl;
        cout << "Right eye: " << rEyeMsg[0] << " " << rEyeMsg[1] << " " << rEyeMsg[2] << " " << rEyeMsg[3] << endl;
    }
    pckg_send_coords(lEyeMsg, rEyeMsg);
    return 0;
}