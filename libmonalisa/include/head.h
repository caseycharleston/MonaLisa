#ifndef HEAD_H
#define HEAD_H

#include "kinematic_link.h

#include <string>

class Head {
protected:
    KinematicLink _head, _eyeL, _eyeR;

public:
    Head();
    Head(std::string filename);
    ~Head();
};

#endif