cmake_minimum_required(VERSION 3.12)
project(test)

# Package dependencies
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Ceres REQUIRED)

# Executables
add_executable(test lisa_driver.cpp client.cpp rigid_transformation.cpp)

# Link to dependencies
target_include_directories(test 
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
${EIGEN_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries (test
    # Link with Eigen
    Eigen3::Eigen

    # Link with OpenCV
    ${OpenCV_LIBS}

    # Link with Boost libraries (e.g., system)
    Boost::system

    # Link with Ceres
    Ceres::ceres
    )





set(CMAKE_CXX_STANDARD 11)  # Choose your desired C++ standard

