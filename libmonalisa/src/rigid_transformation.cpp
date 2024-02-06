#include "rigid_transformation.h"
#include <iostream>
#include <math.h>

using namespace Eigen;
using namespace std;

RigidTransformation::RigidTransformation(
        double tx, double ty, double tz,
        double rx, double ry, double rz, double rw) {
        updateRTMat(tx, ty, tz, rx, ry, rz, rw);;
}

void RigidTransformation::updateRTMat(
        double tx, double ty, double tz, double rx, double ry, double rz, double rw) {
        Eigen::Quaterniond rotQuat(rw, rx, ry, rz);
        Eigen::Matrix<double,3,3> rotMat = rotQuat.toRotationMatrix();
        _rtMat.block<3, 3>(0, 0) = rotMat;  // Copy the rotation matrix
        _rtMat.col(3).head(3) << tx, ty, tz; // Set the translation part
        _rtMat.row(3).head(4) << 0, 0, 0, 1.0;
}

Eigen::Matrix<double,4,4> RigidTransformation::getRTMat(){
        return _rtMat;
}

/*
Eigen::Vector3f RigidTransformation::computeEyeOnScreen(double fx, double fy) {
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

Eigen::Quaternionf RigidTransformation::computeRotationTransformation (double x, double y, double z) {
        cout << "Eye pose: " << endl << eyePose << endl;    
        // this vector contains eye position relative to camera (Mhead * MeyePose)
        Eigen::Vector3f EyePos = eyePose.col(3).head(3);
        cout << "Eye Pos: " << endl << EyePos << endl;

        // this vector contains position of the target
        Eigen::Vector3f target(x, y, z);

        // these vectors contain the vector we want to rotate our eyes to
        Eigen::Vector3f ideal = target - EyePos;
        // ideal.normalize();
        cout << "ideal: " << endl << ideal << endl;

        // contains the original rotation transform (1, 0, 0)
        Eigen::Vector3f originalEyeOrientVect(1, 0, 0);

        // new Quaternion values
        Eigen::Quaternionf newEyeQuaternion = Eigen::Quaternionf::FromTwoVectors(originalEyeOrientVect, ideal);
        cout << "newEyeQuaternion: " << endl << newEyeQuaternion << endl;

        // generate a rotation matrix from the quaternion (Reye_look)
        Eigen::Matrix3f rotationMatrix = newEyeQuaternion.toRotationMatrix();
        cout << "rotationMatrix: " << endl << rotationMatrix << endl;

        // now place rotation matrix into a new matrix (identity matrix)
        Eigen::Matrix4f newRigidTransform = Eigen::Matrix4f::Identity();

        newRigidTransform.block<3, 3>(0, 0) = rotationMatrix;

        // here now multiply pose * leftRigidTransform (same for right eye)
        Eigen::Matrix4f resultPose = eyePose * newRigidTransform;
        cout << "resultPose: " << endl << resultPose << endl;

        // generate quaternion matrix from the new rotation matrix
        Eigen::Quaternionf quaternionToReturn(resultPose.topLeftCorner<3, 3>());
        return quaternionToReturn;
}
*/