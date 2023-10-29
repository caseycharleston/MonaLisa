cmake_minimum_required(VERSION 3.12)
project(calc)

# Find the Eigen package (assuming it's installed on your system)
find_package(Eigen3 REQUIRED)

# Find the OpenCV package (assuming it's installed on your system)
find_package(OpenCV REQUIRED)

# Add your C++ executable or library
add_executable(calc calc.cpp client.cpp)

# Link Eigen and OpenCV to your project
target_include_directories(calc PRIVATE ${EIGEN_INCLUDE_DIR})
target_include_directories(calc PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(calc PRIVATE ${OpenCV_LIBS})

# Other dependencies and source files
# add_dependencies(YourExecutableName ...)
# target_sources(YourExecutableName PRIVATE ...)

# Set C++ standard (optional)
set(CMAKE_CXX_STANDARD 11)  # Choose your desired C++ standard

# You can also add additional compiler flags or optimizations here if needed
# target_compile_options(YourExecutableName PRIVATE ...)

# If you're building a library, use `add_library` instead of `add_executable`
# add_library(YourLibraryName ...)
