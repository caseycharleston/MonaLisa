#ifndef KINEMATIC_LINK_H
#define KINEMATIC_LINK_H

#include "rigid_transformation.h"

class KinematicLink {
protected:
    RigidTransformation _static, _dynamic;
    Eigen::Matrix<double,4,4> _out;

public:
    KinematicLink();
    ~KinematicLink();

    void updateStaticPart(
        float tx, float ty, float tz, float rx, float ry, float rz, float rw);
    void updateDynamicPart(
        float tx, float ty, float tz, float rx, float ry, float rz, float rw);

    void updateOut();
    Eigen::Matrix<double,4,4> getOut();
};

#endif