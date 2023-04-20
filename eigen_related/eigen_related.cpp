#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

class Vec3f : public Eigen::Matrix<float, 3, 1> {
public:

};

class Mat3f : public Eigen::Matrix<float, 3, 3> {
public:

};

template <typename Derived>
Mat3f translate(const Eigen::MatrixBase<Derived>& v) {

}

template <typename Derived>
Vec3f normalize(const Eigen::MatrixBase<Derived>& v) {
    return v.normalized();
}

int main() {
    Vec3f v1{1, 2, 3};
    Vec3f v2 = normalize(v1);
    std::cout << v2 << std::endl;

    return 0;
}