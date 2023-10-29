#include "client.h"

#include <stdio.h>
#include <iostream>
#include <extern/Eigen/Dense>

using namespace std;
// using namespace Eigen;

// File for housing calculations done in C++
// To be sent to the unity project

// Client to demo_server.cs
// SocketClient client("calc");

// Switch that prints out resutling matrices
bool debug = true;

Eigen::Matrix4d calculate_meyelook(Eigen::Matrix4d camera, Eigen::Matrix4d head, Eigen::Matrix4d eye, Eigen::Vector4d tgt);

int main() {
    // Connect to server
    // while (!client.connectToServer());
    // client.send_message("10,10,10");
    // client.send_message("hello");

    // Some infinite loop that will continously listen for input
    // input will be from the visual plane (accept chars assoc. with baby plane)

    // Camera (Fixed)
    Eigen::Matrix4d camera;
    Eigen::Quaterniond Rcamera(0, -1, 0, 1);
    Eigen::Vector3d Pcamera(0, 0, 0);
    camera.setIdentity(); // put [0 0 0 1] on bottom row
    camera.block<3,3>(0,0) = Rcamera.toRotationMatrix();
    camera.block<3,1>(0,3) = Pcamera;
    if (debug) cout << "Camera:" << endl << camera << endl;

    // Head
    double zHead = -1.0; // Changes as needed
    Eigen::Matrix4d head;
    Eigen::Quaterniond Rhead(0, -0.5, 0, 1);
    Eigen::Vector3d Phead(0, 0, zHead);
    head.setIdentity();
    head.block<3,3>(0,0) = Rhead.toRotationMatrix();
    head.block<3,1>(0,3) = Phead;
    if (debug) cout << "Head:" << endl << head << endl;

    // Eyes
    Eigen::Matrix4d leftEye;
    double zLeftEye = zHead - 0.076;
    Eigen::Vector3d pLeftEye(0.13, -0.015, zLeftEye);
    leftEye.setIdentity();
    leftEye.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    leftEye.block<3,1>(0,3) = pLeftEye;
    Eigen::Matrix4d rightEye;
    double zRightEye = zHead + 0.076;
    Eigen::Vector3d pRightEye(0.13, -0.015, zRightEye);
    rightEye.setIdentity();
    rightEye.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    rightEye.block<3,1>(0,3) = pRightEye;
    if (debug) cout << "Left Eye:" << endl << leftEye << endl << "Right Eye:" << endl << rightEye << endl;
    Eigen::Vector4d tgt(1.25, 0, 1.25, 1); // dummy tgt for babyplane 6
    Eigen::Matrix4d mLeftEyeLook = calculate_meyepos(camera, head, leftEye, tgt);
    Eigen::Matrix4d mRightEyeLook = calculate_meyepos(camera, head, rightEye, tgt);
    
    // Send matrices over to Unity
    return 0;
}

// Calculate the eye look rigid transform matrix to be used to change the position
// of an eye from M_head * M_eye_(l,r) to M_eyePose (we are moving the eye to look at a plane)
Eigen::Matrix4d calculate_meyepos(Eigen::Matrix4d camera, Eigen::Matrix4d head, Eigen::Matrix4d eye, Eigen::Vector3d tgt) {
    // subtract the vectors from eyePos and targetPos
    Eigen::Matrix4d truePosOfEye = head * eye; // M_head * M_eye
    Eigen::Vector3d eyePos = truePosOfEye * Eigen::Vector4d(0, 0, 0, 1); // M_eyePose * [0, 0, 0, 1]
    Eigen::Vector3d eyeGaze = tgt - eyePos; // Peye = Ptarget - Peye
    if (debug) cout << "truePosOfEye :" << truePosOfEye << endl << "eyePos: " << eyePos << endl << "eyeGaze: " << eyeGaze << endl;
    cout << "Eye Gaze: " << eyeGaze << endl;

    // Create rot matrix from home pos of eye and eyeGaze
    // Eigen::Matrix3d mRotEyePos = Eigen::Quaterniond::FromTwoVectors(eyeVector, eyeGaze).toRotationMatrix();
    return NULL;
}
