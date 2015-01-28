#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <set>
#include <vector>
#include <math.h>
#include "platform/platform_log.h"

namespace Maths
{

    static const double PI = M_PI;

    template <typename Type>
    class Vector2 {
        Type x;
        Type y;
        public:
        Type GetX() {
            return x;
        }
        Type GetY() {
            return y;
        }
        Type square() const {
            return x*x + y*y;
        }

        Vector2<Type> Clone() const {
            return Vector2<Type>(x, y);
        }

        Vector2(const Vector2& source)
            : x(source.x), y(source.y){
        }
        Vector2(Type x = 0, Type y = 0)
            : x(x), y(y) {
        }
        bool operator<(const Vector2& pt) const {
            if( square() < pt.square() )
                return true;
            if( pt.square() < square() )
                return false;
            if( x < pt.x )
                return true;
            if( pt.x < x)
                return false;
            return y < pt.y;
        }
        Vector2<Type> operator+(const Vector2& pt) {
            x += pt.x;
            y += pt.y;
            return *this;
        }
        Vector2<Type> operator-(const Vector2& pt) {
            x -= pt.x;
            y -= pt.y;
            return *this;
        }

        Vector2<Type> operator*(const int val) {
            x *= val;
            y *= val;
            return *this;
        }

        Vector2<Type> operator/(const int val) {
            x /= val;
            y /= val;
            return *this;
        }
        Vector2<Type> operator%(const int val) {
            x %= val;
            y %= val;
            return *this;
        }
        bool operator=(const Vector2& pt) {
            x = pt.x;
            y = pt.y;
            return true;
        }
        bool operator==(const Vector2& pt) const {
            return x == pt.x && y == pt.y;
        }
        bool operator!=(const Vector2& pt) const {
            return !(*this == pt);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector2& pt) {
            return os << "(" << pt.x << "," << pt.y << ")";
        }
        };

    template <typename Type>
    class Vector4 {
        Type x;
        Type y;
        Type z;
        Type w;
        public:
        Type GetX() {
            return x;
        }
        Type GetY() {
            return y;
        }
        Type GetZ() {
            return z;
        }
        Type GetW() {
            return w;
        }
        Type square() const {
            return x*x + y*y + z*z + w*w;
        }
        Vector4(const Vector4& source)
            : x(source.x), y(source.y), z(source.z), w(source.w){
        }
        Vector4(Type x = 0, Type y = 0, Type z = 0, Type w = 0)
            : x(x), y(y), z(z), w(w) {
        }
        bool operator<(const Vector4& pt) const {
            if( square() < pt.square() )
                return true;
            if( pt.square() < square() )
                return false;
            if( x < pt.x )
                return true;
            if( pt.x < x)
                return false;
            return y < pt.y;
        }
        bool operator+(const Vector4& pt) {
            x += pt.x;
            y += pt.y;
            z += pt.z;
            w += pt.w;
            return true;
        }
        bool operator-(const Vector4& pt) {
            x -= pt.x;
            y -= pt.y;
            z -= pt.z;
            w -= pt.w;
            return true;
        }
        bool operator=(const Vector4& pt) {
            x = pt.x;
            y = pt.y;
            z = pt.z;
            w = pt.w;
            return true;
        }
        bool operator==(const Vector4& pt) const {
            return x == pt.x && y == pt.y && z == pt.z && w == pt.w;
        }
        bool operator!=(const Vector4& pt) const {
            return !(*this == pt);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector4& pt) {
            return os << "(" << pt.x << "," << pt.y << "," << pt.z << "," << pt.w << ")";
        }
    };

    template <typename Type>
    double distanceBetweenPoints(Vector2<Type> v1, Vector2<Type> v2){
        Vector2<Type> v(v2.GetX()-v1.GetX(), v2.GetY()-v1.GetY());

        return sqrt(v.square());
    }

}

#endif // VECTOR_H
