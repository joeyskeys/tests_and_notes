find_package(Eigen3 REQUIRED)

add_executable(eigen_related eigen_related.cpp)

target_include_directories(eigen_related PRIVATE ${EIGEN3_INCLUDE_DIRS})