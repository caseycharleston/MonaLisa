#include <iostream>
#include <ceres/ceres.h>
#include <Eigen/Dense>

struct ProjectionCostFunction {
    //add parameters + rigid tranform matrix for mona eyePose + grid points
    ProjectionCostFunction(const Eigen::Matrix<double, 3, 1>& regular_proj,
                           const Eigen::Matrix<double, 4, 3>& mona_3d,
                           const Eigen::Matrix<double, 64, 64>& grid_points)
        : regular_projection_matrix(regular_proj, mona_3d, grid_points){}

    template <typename T>
    //add f, z, as parameters
    bool operator()(const T* const z, const T* const f, T* residual) const {
        // Create Eigen matrices from regular_projection_matrix and updated_proj_mat

        //compute mona gaze vector
        Eigen::Matrix<double, 4, 3> camera_proj;
        camera proj << f[0], 0, 0, 0,
                       0, f[0], 0, 0,
                       0, 0, 1, 0;
        Eigen::Matrix<double, 4, 1> origin;
        origin<< 0,
                 0,
                 0,
                 z[0]; 

        Eigen::Matrix<double, 3, 1> mona_proj = mona_3d * camera_proj * origin;

        residual[0] = regular_proj - mona_proj;
        
        return true;
    }

    static ceres::CostFunction* Create(const Eigen::Matrix<double, 3, 1>& regular_proj,
                                       const Eigen::Matrix<double, 4, 3>& mona_3d,
                                       const Eigen::Matrix<double, 64, 64>& grid_points) {
        return new ceres::AutoDiffCostFunction<ProjectionCostFunction, 6, 1>(
            new ProjectionCostFunction(regular_proj, mona_3d, grid_points)
        );
    }

    const Eigen::Matrix<double, 4, 1>& regular_proj;
    const Eigen::Matrix<double, 4, 3>& mona_3d;
    const Eigen::Matrix<double, 64, 64>& grid_points;
};

int main() {
    // Define your regular and updated projection matrices

    double focal_length = 50;
    double z_distance = 0;

    Eigen::Matrix<double, 4, 3> reg_coordinates;
    Eigen::Matrix<double, 4, 3> mona_coordinates;
    Eigen::Matrix<double, 64, 64> grid_points;

    Eigen::Matrix<double, 4, 3> camera_proj;
    camera proj << 50, 0, 0, 0,
                    0, 50, 0, 0,
                    0, 0, 50, 0;
    Eigen::Matrix<double, 4, 1> origin;
    origin << 0, 
              0,
              0,
              1;

    Eigen::Matrix<double, 3, 1> reg_projection = camera_proj * origin;

    // Set up the Ceres Solver problem
    ceres::Problem problem;

    // Add the cost function to the problem
    problem.AddResidualBlock(
        ProjectionCostFunction::Create(reg_projection, mona_3d, grid_points),
        nullptr, // Loss function (nullptr for default)
        z_distance, 
        focal_length // The parameters to be optimized 
    );

    // Set up the solver options
    ceres::Solver::Options options;

    ceres::Solver::Summary summary;
    
    // Solve the problem
    ceres::Solve(options, &problem, &summary);

    // Output the results
    std::cout << summary.BriefReport() << "\n";
    std::cout << "Regular Projection Matrix:\n" << regProjection << "\n";
    std::cout << "Updated Projection Matrix (with optimized z):\n" << monaProjection << "\n";

    return 0;
}

