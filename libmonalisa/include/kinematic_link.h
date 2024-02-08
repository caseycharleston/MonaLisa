#ifndef KINEMATIC_LINK_H
#define KINEMATIC_LINK_H

#include "rigid_transformation.h"

class KinematicLink {
protected:
    RigidTransformation _static, _dynamic;
    // ?
    Eigen::Matrix<double,4,4> _out;

public:
    KinematicLink();
    ~KinematicLink();

    void updateStaticPart(
        double tx, double ty, double tz, double rx, double ry, double rz, double rw);
    void updateDynamicPart(
        double tx, double ty, double tz, double rx, double ry, double rz, double rw);
    Eigen::Quaterniond rotateDynamicPart(double x, double y, double z);
    Eigen::Quaterniond getRotationQuaternions();
    // ?
    void updateOut();
    Eigen::Matrix<double,4,4> getOut();
};

#endif