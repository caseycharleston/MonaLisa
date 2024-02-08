#ifndef HEAD_H
#define HEAD_H

#include "kinematic_link.h"

#include <iostream>
#include <fstream>
#include <string>

class Head {
protected:
    KinematicLink _head, _eyeL, _eyeR;

public:
    Head();
    Head(std::string filename);
    ~Head();
    // rotate the eyes to look at a certain point
    void rotateEyes(double x, double y, double z);
    KinematicLink *getDynamicRightEye();
    KinematicLink *getDynamicLeftEye();  
    // Eigen::Matrix<double,4,4> KinematicLink::getOutHead();
    // Eigen::Matrix<double,4,4> KinematicLink::getEyeL();
    // Eigen::Matrix<double,4,4> KinematicLink::getEyeR();
    void getParameters(std::string positions, std::string rotations, double *toReturn);
};

#endif