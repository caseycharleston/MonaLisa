#include "rigid_transformation.h"
#include <iostream>

using namespace Eigen;
Eigen::Vector3f RigidTransformation::computeEyeOnScreen(float fx, float fy) {
        // create camera projection Pcamera
        // here we are making the assumption that camera is center of the coordinate system
        Eigen::MatrixXf pCamera(3, 4);
        pCamera << fx, 0, 0, 0, 
                   0, fy, 0, 0,
                   0, 0, 1, 0;

        // take current leftEyePose and rightEyePose and extract the positions, then multiply it by camera projection matrix
        Eigen::Vector3f EyeOnScreen = pCamera * eyePose.col(4);

        // this array contains the 2D coordinates eye projections
        return EyeOnScreen.head(2);
}

Eigen::Quaternionf RigidTransformation::computeRotationTransformation (float x, float y, float z) {
        // this vector will contain our original eye position **CHANGE**
        Eigen::Vector3f EyePos = eyePose.col(3).head(3);

        // this vector contains position of the target
        Eigen::Vector3f target(x, y, z);

        // these vectors contain the vector we want to rotate our eyes to
        Eigen::Vector3f ideal = target - EyePos;
        ideal.normalize();

        // **MAYBE CHANGE** contains the original rotation transform (1, 0, 0)
        Eigen::Vector3f originalEyeOrientVect(1, 0, 0);

        // new Quaternion values
        Eigen::Quaternionf newEyeQuaternion = Eigen::Quaternionf::FromTwoVectors(originalEyeOrientVect, ideal);

        // generate a rotation matrix from the quaternion (Reye_look)
        Eigen::Matrix3f rotationMatrix = newEyeQuaternion.toRotationMatrix();

        // now place rotation matrix into a new matrix (identity matrix)
        Eigen::Matrix4f newRigidTransform = Eigen::Matrix4f::Identity();

        newRigidTransform.block<3, 3>(0, 0) = rotationMatrix;

        // here now multiply pose * leftRigidTransform (same for right eye)
        Eigen::Matrix4f resultPose = eyePose * newRigidTransform;

        // generate quaternion matrix from the new rotation matrix
        Eigen::Quaternionf quaternionToReturn(resultPose.topLeftCorner<3, 3>());

        // return the generated quaternion
        return quaternionToReturn;
}

void RigidTransformation::update(float tx, float ty, float tz, float rx, float ry, float rz, float rw) {
            Eigen::Quaternionf rotQuat(rw, rx, ry, rz);
            Eigen::Matrix<float,3,3> rotMat = rotQuat.toRotationMatrix();
            eyePose.block<3, 3>(0, 0) = rotMat;  // Copy the rotation matrix
            eyePose.col(3).head(3) << tx, ty, tz; // Set the translation part
            eyePose(3, 3) = 1.0; // Set the bottom-right element
}