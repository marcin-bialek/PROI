//  PROI project 2
//  Marcin Białek


#include <Vector3D.h>
#include <cmath>



double Vector3D::length() const {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}



Vector3D Vector3D::unitVector() const {
    return *this / length();
}



double Vector3D::dot(const Vector3D &v) const {
    return v.x * x + v.y * y + v.z * z;
}



Vector3D Vector3D::cross(const Vector3D &v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}



bool operator==(const Vector3D &v, const Vector3D &w) {
    return (v.x == w.x) && (v.y == w.y) && (v.z == w.z);
}



Vector3D operator+(const Vector3D &v, Vector3D w) {
    return { v.x + w.x, v.y + w.y, v.z + w.z };
}



Vector3D operator-(const Vector3D &v, Vector3D w) {
    return { v.x - w.x, v.y - w.y, v.z - w.z };
}



Vector3D operator*(Vector3D v, double s) {
    return { v.x * s, v.y * s, v.z * s };
}



Vector3D operator*(double s, Vector3D v) {
    return v * s;
}



double operator*(const Vector3D &v, Vector3D w) {
    return v.dot(w);
}



Vector3D operator/(Vector3D v, double s) {
    return { v.x / s, v.y / s, v.z / s };
}



std::ostream& operator<<(std::ostream &stream, const Vector3D &v) {
    return stream << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
}


