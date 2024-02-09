#include "kinematic_link.h"

KinematicLink::KinematicLink() {
    // here update the kinematic link (static in relation to the head)

    // here update the kinematic link (dynamic in relation to everything else)
    
}
KinematicLink::~KinematicLink() {


}

void KinematicLink::updateStaticPart(
    double tx, double ty, double tz, double rx, double ry, double rz, double rw) {
    _static.updateRTMat(tx, ty, tz, rx, ry, rz, rw);
}

void KinematicLink::updateDynamicPart(
    double tx, double ty, double tz, double rx, double ry, double rz, double rw) {
    _dynamic.updateRTMat(tx, ty, tz, rx, ry, rz, rw);
}

// update the dynamic part and return the quaternions of its new rotation transform
Eigen::Quaterniond KinematicLink::rotateDynamicPart(double x, double y, double z) {
    return _dynamic.computeRotationTransformation(x, y, z);
}

// return the quaternions for the current dynamic rotation transformation
Eigen::Quaterniond KinematicLink::getRotationQuaternions() {
    return _dynamic.getQuaternions();
}

void KinematicLink::updateOut() {
    _out = _static.getRTMat() * _dynamic.getRTMat();
}

Eigen::Matrix<double,4,4> KinematicLink::getOut() {
    return _out;
}