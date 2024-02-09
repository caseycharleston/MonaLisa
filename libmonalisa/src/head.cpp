#include "head.h"
#include <fstream>
#include <string>

using namespace std;

// initialize head in default vals
Head::Head() {
    _head.updateDynamicPart(-1.00, 0.00, 0.00, 0.00000, 0.00000, 0.00000, 1.00000);
    _eyeR.updateDynamicPart(-0.87, -0.02, 0.08, 0.00000, 0.00000, 0.00000, 1.00000);
    _eyeL.updateDynamicPart(-0.87, -0.02, -0.08, 0.00000, 0.00000, 0.00000, 1.00000);
}


Head::Head(std::string filename) {
    // here instatntiate the pose of the _head and its eyes
    //KinematicLink _head, _eyeL, _eyeR;
    //file must have this format;
    // Default head position:
    // -1.00 0.00 0.00
    // Default head quaternions:
    // 0.00000 0.00000 0.00000 1.00000
    // Default rightEye position:
    // -0.87 -0.02 0.08
    // Default rightEye quaternions:
    // 0.00000 0.00000 0.00000 1.00000
    // Default leftEye position:
    // -0.87 -0.02 0.08
    // Default leftEye quaternions:
    // 0.00000 0.00000 0.00000 1.00000
    // ** IMPORTANT ** VALUES MUST BE STORED IN ODD NUMBERED LINES AND MUST HAVE A SPACE AT THE END
    ifstream inFile;
    inFile.open(filename);
    string headPos, headRot, rightPos, rightRot, leftPos, leftRot;
    string s;
    int lineNum = 1;
    while(getline(inFile, s)) {
        cout << "in function" << endl;
        if (lineNum % 2 == 0) {
            if (lineNum == 2) {
                headPos = s;
            } else if (lineNum == 4) {
                headRot = s;
            } else if (lineNum == 6) {
                rightPos = s;
            } else if (lineNum == 8) {
                rightRot = s;
            } else if (lineNum == 10) {
                leftPos = s;
            } else if (lineNum == 12) {
                leftRot = s;
            }
        }
        lineNum++;
    }
    cout << "headPos line: " << headPos << endl;
    cout << "headRot line: " << headRot << endl;
    cout << "rightPos line: " << rightPos << endl;
    cout << "rightRot line: " << rightRot << endl;
    cout << "leftPos line: " << leftPos << endl;
    cout << "leftRot line: " << leftRot << endl;
    cout << "\n";
    
    double *headVals = new double[7];
    getParameters(headPos, headRot, headVals);
    cout << "the head vals: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << headVals[i] << " ";
    }
    cout << "\n\n\n";
    double *rightVals = new double[7];
    getParameters(rightPos, rightRot, rightVals);
    cout << "the right vals: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << rightVals[i] << " ";
    }
    cout << "\n";

    // cout << "\n\n\n";
    double *leftVals = new double[7];
    getParameters(leftPos, leftRot, leftVals);
    cout << "the left vals: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << leftVals[i] << " ";
    }
    cout << "\n";
    // (0.00000, 0.00000, 0.00000, 1.00000)
    _head.updateDynamicPart(headVals[0], headVals[1], headVals[2], headVals[3], headVals[4], headVals[5], headVals[6]);
    _eyeR.updateDynamicPart(rightVals[0], rightVals[1], rightVals[2], rightVals[3], rightVals[4], rightVals[5], rightVals[6]);
    _eyeL.updateDynamicPart(leftVals[0], leftVals[1], leftVals[2], leftVals[3], leftVals[4], leftVals[5], leftVals[6]);
}

Head::~Head() {}


// Eigen::Matrix<double,4,4> KinematicLink::getOutHead() {
//     return _head.getOut();
// }

// Eigen::Matrix<double,4,4> KinematicLink::getEyeL() {
//     return _head.getOut() * _eyeL.getOut();
// }

// Eigen::Matrix<double,4,4> KinematicLink::getEyeR() {
//     return _head.getOut() * _eyeR.getOut();
// }

void Head::rotateEyes(double x, double y, double z) {
    _eyeL.rotateDynamicPart(x, y, z);
    _eyeR.rotateDynamicPart(x, y, z);
}

KinematicLink *Head::getDynamicRightEye() {
    return &_eyeR;
}       

KinematicLink *Head::getDynamicLeftEye() {
    return &_eyeL;
}       

// helper method for parsing a file, given two strings, parses then and returns its doubles 
// used for reading values from a file
void Head::getParameters(string positions, string rotations, double *toReturn) {
    int index = 0;
    size_t pos = 0;
    string delimiter = " ";
    string token;
    while ((pos = positions.find(delimiter)) != string::npos && index < 3) {
        token = positions.substr(0, pos);
        double value = strtod(token.c_str(), NULL);
        toReturn[index] = value;
        index++;
        positions.erase(0, pos + delimiter.length());
    }
    pos = 0;
    while ((pos = rotations.find(delimiter)) != string::npos) {
        token = rotations.substr(0, pos);
        double value = strtod(token.c_str(), NULL);
        toReturn[index] = value;
        index++;
        rotations.erase(0, pos + delimiter.length());
    }
}