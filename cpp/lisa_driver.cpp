#include "client.h"
#include "rigid_transformation.h"
// #include "optimize.cpp"

#include <iostream>
#include <cstdio>
#include <string.h>
#include <math.h>
#include <fstream>
#include <ctime>
#include <random>

using namespace std;

bool debug = true;
Client myClient("LisaDriver");
string resultsFolder = "../../Results";

void setup_environment(ofstream& file) {
    cout << "Accepting input for environment variables..." << endl;
    file << "### Environment variables ###" << endl;

    // camPos
    cout << "Camera position - Enter a float value (default 0): ";
    string input;
    cin >> input;
    if (input.length() == 0) {
        input = "0";
    }
    myClient.sendMessage(input);
    file << "camera position: " << input << endl;

    input = "";
    cout << "Head distance - Enter a float value (default -1): ";
    cin >> input;
    if (input.length() == 0) {
        input = "-1";
    }
    myClient.sendMessage(input);
    file << "head distance: " << input << endl;

    input = "";
    cout << "Target distance - Enter a float value (default 1): ";
    cin >> input;
    if (input.length() == 0) {
        input = "1";
    }
    myClient.sendMessage(input);
    file << "target distance: " << input << endl;

    input = "";
    cout << "monitor size - Enter a string value in the form of \"wxh\". " << endl << "For example, 20x10 (default 0x0): ";
    cin >> input;
    if (input.length() == 0) {
        input = "0x0";
    }
    myClient.sendMessage(input);
    file << "monitor size: " << input << endl;

    input = "";
    cout << "monitor resolution - Enter a string value in the form of \"yxz\". " << endl << "For example, 1920x1080 (default 1920x1080): ";
    cin >> input;
    if (input.length() == 0) {
        input = "1920x1080";
    }
    myClient.sendMessage(input);
    file << "monitor resolution: " << input << endl;

    cout << "Environment setup finished." << endl;
}

// Package send an array of 6 floats (first 3 are rot coords for the left eye, second 3 are rot coords for the right eye)
void pckg_send_coords(float eye1[], float eye2[]) {
    // concatenate values to conform to the expected message format in Unity Controller.cs
    string msg = to_string(eye1[0]) + "," + to_string(eye1[1]) + "," + to_string(eye1[2]) + "," + to_string(eye1[3]) + ","
                + to_string(eye2[0]) + "," + to_string(eye2[1]) + "," + to_string(eye2[2]) + "," + to_string(eye2[3]);
    myClient.sendMessage(msg);
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
    // if (!myClient.ConnectToServer("127.0.0.1", 12345)) {
    //     cout << "Failed to connect to server. Exiting.";
    //     return 0;
    // }
    // // Create txt file for this experiment run
    // Get current timestamp
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d_%H-%M-%S");
    std::string timestamp = oss.str();

    std::string filename = "results@" + timestamp + ".txt";
    std::ofstream file(resultsFolder + "/" + filename);
    // populate environment variables in Unity.
    // setup_environment(file);

    // *** MAIN EXPERIMENT LOOP ***
    file << endl << "### RESULTS ###" << endl << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 15);

    int count = 1;

    while (true) {
        file << "trial " << count << " | ";
        // Select model (Normal or Mona Lisa)
        int lisa;
        cout << "Enter 0 for normal head, 1 for mona lisa head: ";
        cin >> lisa;
        file << "Model: ";
        if (lisa == 1) {
            file << "Mona Lisa | ";
        } else {
            file << "Normal | ";
        }
        // Obtain random square to look at
        // TODO: copy down baby square positions in this file to pass onto computeRotationTransformation
        // Probably should make it a <char, (x,y,z)> mapping to write chars to results
        int randomSquare = dis(gen);
        cout << "Picked random square: " << randomSquare << endl;
        file << "Gazed Square: " << randomSquare << " | ";

        cout << "Input participant guess as the letter they guessed: ";
        char guess;
        cin >> guess;
        file << "Guessed Square: " << guess << " | ";

        file << "Was correct? ";
        // TODO: change randomSquare to char representation
        if (guess == randomSquare) {
            file << "Yes | ";
        } else {
            file << " No | ";
        }

        file << endl;
        file.flush(); // ensure result is written down in file
        count++;
    }

    // // RIGID TRANSFORM OBJECT
    // float headDist = 1.0;
    // RigidTransformation leftEye(0.13 + -headDist, -0.015, -0.076, 0, 0, 0, 1);
    // RigidTransformation rightEye(0.13 + -headDist, -0.015, 0.076, 0, 0, 0, 1);

    // /*
    //     Plug in values here of target position
    // */
    // Eigen::Quaternionf leftEyeRT = leftEye.computeRotationTransformation(1, 0.1125, 0.3375);
    // Eigen::Quaternionf rightEyeRT = rightEye.computeRotationTransformation(1, 0.1125, 0.3375);

    // // A
    // // Eigen::Quaternionf leftEyeRT = leftEye.computeRotationTransformation(1, 0.3375, 0.3375);
    // // Eigen::Quaternionf rightEyeRT = rightEye.computeRotationTransformation(1, 0.3375, 0.3375);

    // Eigen::Vector4f lCoeffs = leftEyeRT.coeffs();
    // Eigen::Vector4f rCoeffs = rightEyeRT.coeffs();
    // if (debug) {
    // // Displaying the results
    //     std::cout << "Left Eye" << endl;
    //     std::cout << "Quaternion: " << lCoeffs.transpose() << std::endl;
    //     std::cout << "Right Eye" << endl;
    //     std::cout << "Quaternion: " << rCoeffs.transpose() << std::endl;
    // }

    // char answer = 'n';
    // cout << "type 'y' to continue" << endl;
    // while (answer != 'y')
    //     cin >> answer;
    
    // // w, x, y, z
    // float lEyeMsg[] = {lCoeffs(0), lCoeffs(1), lCoeffs(2), lCoeffs(3)};
    // float rEyeMsg[] = {rCoeffs(0), rCoeffs(1), rCoeffs(2), rCoeffs(3)};

    // // RadiansToDegrees(lEyeMsg);
    // // RadiansToDegrees(rEyeMsg);
    // if (debug) {
    //     cout << "Values to send: " << endl;
    //     cout << "Left eye: " << lEyeMsg[0] << " " << lEyeMsg[1] << " " << lEyeMsg[2] << " " << lEyeMsg[3] << endl;
    //     cout << "Right eye: " << rEyeMsg[0] << " " << rEyeMsg[1] << " " << rEyeMsg[2] << " " << rEyeMsg[3] << endl;
    // }
    // pckg_send_coords(lEyeMsg, rEyeMsg);
    return 0;
}