#ifndef RIGID_TRANSFORMATION_H
#define RIGID_TRANSFORMATION_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

//template <typename T>
class RigidTransformation {
protected:
    // this matrix contains the pose of an eye (right or left and regular or monaLisa)
    Eigen::Matrix<double,4,4> _rtMat;

public:
    RigidTransformation(
        double tx = 0.0, double ty = 0.0, double tz = 0.0,
        double rx = 0.0, double ry = 0.0, double rz = 0.0, double rw = 1.0);
        
    ~RigidTransformation() {}

    void updateRTMat(
        double tx = 0.0, double ty = 0.0, double tz = 0.0,
        double rx = 0.0, double ry = 0.0, double rz = 0.0, double rw = 1.0);

    Eigen::Matrix<double,4,4> getRTMat();

    // compute transformation from 3d coordinates to 2d based on focal lengths (projection of eye onto screen)
    // Eigen::Vector3f computeEyeOnScreen(double fx, double fy);

    // Compute the transformation to make eye look at target (normal head). returns quaternion
    // Eigen::Quaternionf computeRotationTransformation(double x, double y, double z);
};

#endif