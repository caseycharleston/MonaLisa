#include "rigid_transformation.h"

class RobotHead {
private:
// Initialize the eyes with initial offsets and a reference to the head
// note: update this with the right values later
    RobotEyes right_eye{1.0f, 0.5f, 0.5f, this};  
    RobotEyes left_eye{1.0f, 0.5f, 0.5f, this};  
public:
    float x, y, z; // coordinates of head in Unity
    
    // grid target to look at; default set this to middle grid
    
    // note: initialize with with proper coordinates
    Eigen::MatrixXd grid_point; 

    RobotHead(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
    
    // moves head and eyes relative to head
    void move_head(float update_x, float update_y, float update_z);
    void update_target(Eigen::MatrixXd new_grid_point);
}

class RobotEyes {
public: 
    float x, y, z;
    RobotHead* my_head; // reference to associated head
    Eigen::Matrix<float,4,4> eyePose; // rigid transformation of eye

    Eyes(float _x, float _x, float _z, RobotHead* _head) : x(_x), y(_y), z(_z), my_head(head) {}

    // move eyes relative to the head
    void update_eye_position();
}

