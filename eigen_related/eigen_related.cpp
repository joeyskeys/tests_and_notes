#include <iostream>

#include <Eigen/Core>

class Vec3f : public Eigen::Matrix<float, 3, 1> {
public:

};

Vec3f normalize(const Vec3f& v) {
    return v.normalized();
}

int main() {
    Vec3f v1{1, 2, 3};
    Vec3f v2 = normalize(v1);
    std::cout << v2 << std::endl;

    return 0;
}