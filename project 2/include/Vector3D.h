//  PROI project 2
//  Marcin Białek


#pragma once
#include <iostream>


class Vector3D {
    double x = 0, y = 0, z = 0;
    
public:
    Vector3D() {};
    Vector3D(double x, double y, double z): x(x), y(y), z(z) {}
    
    double length() const;
    Vector3D unitVector() const;
    double dot(const Vector3D &v) const;
    Vector3D cross(const Vector3D &v) const;
    
    friend bool operator==(const Vector3D &v, const Vector3D &w);
    friend Vector3D operator+(const Vector3D &v, Vector3D w);
    friend Vector3D operator-(const Vector3D &v, Vector3D w);
    friend Vector3D operator*(Vector3D v, double s);
    friend Vector3D operator*(double s, Vector3D v);
    friend double operator*(const Vector3D &v, Vector3D w);
    friend Vector3D operator/(Vector3D v, double s);
    friend std::ostream& operator<<(std::ostream &stream, const Vector3D &v);
};
