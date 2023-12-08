#ifndef RIGID_TRANSFORMATION_H
#define RIGID_TRANSFORMATION_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

//template <typename T>
class RigidTransformation {
protected:
    // this matrix contains the pose of an eye (right or left and regular or monaLisa)
    Eigen::Matrix<float,4,4> eyePose;

public:
    RigidTransformation(
        float tx = 0.0, float ty = 0.0, float tz = 0.0,
        float rx = 0.0, float ry = 0.0, float rz = 0.0, float rw = 1.0) {
        update(tx, ty, tz, rx, ry, rz, rw);
    }
    ~RigidTransformation() {}

    // compute transformation from 3d coordinates to 2d based on focal lengths (projection of eye onto screen)
    Eigen::Vector3f computeEyeOnScreen(float fx, float fy);

    // Compute the transformation to make eye look at target (normal head). returns quaternion
    Eigen::Quaternionf computeRotationTransformation(float x, float y, float z);

    // fills the eyePose  with designated values
    void update(float tx, float ty, float tz, float rx, float ry, float rz, float rw);
};

#endif