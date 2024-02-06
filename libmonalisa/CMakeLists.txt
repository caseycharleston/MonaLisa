cmake_minimum_required(VERSION 3.12)
project(lisa_driver)

# Package dependencies
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Ceres REQUIRED)

# Executables
add_executable(
    lisa_driver
    # src/lisa_driver.cpp
    # src/client.cpp
    src/kinematic_link.cpp
    src/rigid_transformation.cpp
    src/test.cpp
)

# Link to dependencies
target_include_directories(lisa_driver 
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
${EIGEN_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries (lisa_driver
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

