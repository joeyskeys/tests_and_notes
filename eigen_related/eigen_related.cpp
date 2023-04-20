#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

class Vec3f : public Eigen::Matrix<float, 3, 1> {
public:
    using Base = Eigen::Matrix<float, 3, 1>;

    template <typename ...Ts, typename = std::enable_if_t<sizeof...(Ts) == 3 && (... && std::is_arithmetic_v<Ts>)>>
    Vec3f(Ts... args) : Base(static_cast<float>(args)...) {}

    template <typename Derived>
    Vec3f(const Eigen::MatrixBase<Derived>& p) : Base(p) {}

    template <typename Derived>
    Vec3f &operator =(const Eigen::MatrixBase<Derived>& p) {
        this->Base::operator=(p);
        return *this;
    }
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
