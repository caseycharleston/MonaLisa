#include <ceres/ceres.h>
#include <Eigen/Dense>
/*Defines the Cost Function for optimization*/
struct CostFunctor {
    CostFunctor(const Eigen::Vector3d& regProj) : regProj_(regProj) {}

    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        // Construct the homogeneous vector Ptwo with x as the third component
        Eigen::Matrix<T, 3, 1> mlProj;
        mlProj << regProj_.template cast<T>().head(2), x[0];

        // Compute the residual as the difference between regular and mona lisa
        Eigen::Map<Eigen::Matrix<T, 3, 1>> residual_map(residual);
        residual_map = regProj_.template cast<T>() - mlProj;

        return true;
    }

    private:
        const Eigen::Vector3d regProj_;
};


int main() {
  // get regular projection from Unity code and initialize this variable
  Eigen::Vector3d regProj;
  // get mona lisa projection from Unity Code and initialize
  Eigen::Vector3d mlProj_initial; 

  ceres::Problem problem;

  ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction <CostFunctor, 3, 1>(new CostFunctor(regProj));
  problem.AddResidualBlock(cost_function, nullptr, mlProj_initial.data());

  // Configure solver options
  ceres::Solver::Options options;
  options.minimizer_progress_to_stdout = true;

  // Run the solver
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);

  // Output results
  std::cout << summary.FullReport() << std::endl;

  // Retrieve the optimized mona lisa projection (zero out x and y)
  Eigen::Vector3d ML_Optimized;
  ML_Optimized << 0.0, 0.0, mlProj_initial[0];
  std::cout << "Optimized mona lisa:\n" << ML_Optimized << std::endl;

  return 0;
}
