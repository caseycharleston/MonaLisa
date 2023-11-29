#include "RigidTransformation.hpp"
#include <iostream>
    
Eigen::Vector2f RigidTransformation::computeEyeOnScreen(float fx, float fy) {
        // create camera projection Pcamera
        // here we are making the assumption that camera is center of the coordinate system
        Eigen::MatrixXd pCamera(3, 4);
        pCamera << fx, 0, 0, 0, 
                   0, fy, 0, 0,
                   0, 0, 1, 0;

        // take current leftEyePose and rightEyePose and extract the positions, then multiply it by camera projection matrix
        Eigen::Vector3d EyeOnScreen = pCamera * eyePose.col(3);

        // this array contains the 2D coordinates eye projections
        return EyeOnScreen.head(2);
}

Eigen::Quaternionf RigidTransformation::computeRotationTransformation (float x, float y, float z) {
        // this vector will contain our original eye position **CHANGE**
        Eigen::Vector3f EyePos = eyePose.col(3).head(3);

        // this vector contains position of the target
        Eigen::Vector3d target(x, y, z);

        // these vectors contain the vector we want to rotate our eyes to
        Eigen::Vector3d ideal = target - EyePos;
        ideal.normalize();

        // **MAYBE CHANGE** contains the original rotation transform (1, 0, 0)
        Eigen::Vector3d originalEyeOrientVect(1, 0, 0);

        // new Quaternion values
        Eigen::Quaternionf newEyeQuaternion = Eigen::Quaternionf::FromTwoVectors(originalEyeOrientVect, ideal);

        // generate a rotation matrix from the quaternion (Reye_look)
        Eigen::Matrix3d rotationMatrix = newEyeQuaternion.toRotationMatrix();

        // now place rotation matrix into a new matrix (identity matrix)
        Eigen::Matrix4d newRigidTransform = Eigen::Matrix4d::Identity();

        newRigidTransform.block<3, 3>(0, 0) = rotationMatrix;

        // here now multiply pose * leftRigidTransform (same for right eye)
        Eigen::Matrix4d resultPose = eyePose * newRigidTransform;

        // generate quaternion matrix from the new rotation matrix
        Eigen::Quaternionf quaternionToReturn(resultPose.topLeftCorner<3, 3>());

        // return the generated quaternion
        return quaternionToReturn;
}

void RigidTransformation::update(float tx, float ty, float tz, float rx, float ry, float rz, float rw) {
            Eigen::Quaternionf rotQuat(rw, rx, ry, rz);
            Eigen::Matrix<float,3,3> rotMat = rotQuat.toRotationMatrix();
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    eyePose(i,j) = rotMat(i,j);
                }
            }
            //_rigidTransformation.block<T, 0, 0, 3, 3> = rotQuat.toRotationMatrix();
            eyePose(0,3) = tx;
            eyePose(1,3) = ty;
            eyePose(2,3) = tz;
            eyePose(3,3) = 1.0;
}