#include <iostream>
#include <ceres/ceres.h>
#include <Eigen/Dense>

struct ProjectionCostFunction {
    ProjectionCostFunction(const Eigen::Matrix<double, 4, 1>& regProjMat,
                           const Eigen::Matrix<double, 4, 1>& monaProjMat)
        : regular_projection_matrix(regProjMat),
          updated_projection_matrix(monaProjMat) {}

    template <typename T>
    bool operator()(const T* const z, T* residual) const {
        // Create Eigen matrices from regular_projection_matrix and updated_proj_mat
        Eigen::Map<const Eigen::Matrix<T, 4, 1>> reg_proj_mat(regProjMat.data());
        Eigen::Map<Eigen::Matrix<T, 4, 1>> mona_proj_mat(monaProjMat.data());
        
        // Update 3rd row, first column (z value of matrix)
        monaProjMat(2, 0) = z[0];

        // Compute the difference between regular_proj_mat and updated_proj_mat
        Eigen::Matrix<T, 4, 1> diff = regProjMat - monaProjMat;

        // Flatten the difference matrix into the residual array
        Eigen::Map<Eigen::Matrix<T, 8, 1>> residual_map(residual);
        residual_map = Eigen::Map<const Eigen::Matrix<T, 8, 1>>(diff.data());

        return true;
    }

    static ceres::CostFunction* Create(const Eigen::Matrix<double, 4, 1>& regProjMat,
                                       const Eigen::Matrix<double, 4, 1>& monaProjMat) {
        return new ceres::AutoDiffCostFunction<ProjectionCostFunction, 8, 1>(
            new ProjectionCostFunction(regProjMat, monaProjMat)
        );
    }

    const Eigen::Matrix<double, 4, 1>& regProjMat;
    const Eigen::Matrix<double, 4, 1>& monaProjMat;
};

int main() {
    // Define your regular and updated projection matrices
    Eigen::Matrix<double, 4, 1> regProjection;
    Eigen::Matrix<double, 4, 1> monaProjection;

    // Set up the Ceres Solver problem
    ceres::Problem problem;

    // Add the cost function to the problem
    problem.AddResidualBlock(
        ProjectionCostFunction::Create(regProjection, monaProjection),
        nullptr, // Loss function (nullptr for default)
        monaProjection(2, 0).data() // The parameter to be optimized (z)
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
