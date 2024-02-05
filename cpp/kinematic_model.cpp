#include <kinematic_model.hpp>

using namespace Eigen;
using namespace std;

void move_head(float update_x, float update_y, float update_z) {
    x += update_x;
    y += update_y;
    z += update_z;

    //update eyes' reference to head
    right_eye.my_head = this;
    left_eye.my_head = this;

    right_eye.update_eye_position(update_x, update_y, update_z);
    left_eye.update_eye_position(update_x, update_y, update_z);
}

void update_eye_position(float _x, float _y, float _z) {
    x += _x;
    y += _y;
    z += _z;

    // note: decompose to x, y, z coordinates 
    // float grid_x = my_head.grid_point[0];
    // float grid_y = my_head.grid_point[1];
    // float grid_z = my_head.grid_point[2];

    // re-compute eye_pose
    // note: update this method to account for moving eyes
    computeRotationTransformation(grid_x, grid_y, grid_z);
}