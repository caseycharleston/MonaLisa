#include "kinematic_link.h"

KinematicLink::KinematicLink() {}
KinematicLink::~KinematicLink() {}

void KinematicLink::updateStaticPart(
    float tx, float ty, float tz, float rx, float ry, float rz, float rw) {
    _static.updateRTMat(tx, ty, tz, rx, ry, rz, rw);
}

void KinematicLink::updateDynamicPart(
    float tx, float ty, float tz, float rx, float ry, float rz, float rw) {
    _dynamic.updateRTMat(tx, ty, tz, rx, ry, rz, rw);
}

void KinematicLink::updateOut() {
    _out = _static.getRTMat() * _dynamic.getRTMat();
}

Eigen::Matrix<double,4,4> KinematicLink::getOut() {
    return _out;
}