#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <set>
#include <vector>

namespace Maths
{

    template <typename Type>
    class Vector2 {
        Type x;
        Type y;
    public:
      Type GetX() { return x; }
      Type GetY() { return y; }
      Type square() const { return x*x + y*y; }
      Vector2(const Vector2& source)
        : x(source.x), y(source.y){}
      Vector2(Type x = 0, Type y = 0, Type z = 0)
        : x(x), y(y) {}
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
        bool operator+(const Vector2& pt) {
            x += pt.x;
            y += pt.y;
            return true;
      }
        bool operator-(const Vector2& pt) {
            x -= pt.x;
            y -= pt.y;
            return true;
      }
        bool operator=(const Vector2& pt) {
            x = pt.x;
            y = pt.y;
            return true;
      }
        bool operator==(const Vector2& pt) const {
            if (x == pt.x && y == pt.y){
                return true;
            }else{
                return false;
            }
      }
        bool operator!=(const Vector2& pt) const {
          return !(*this == pt);
      }

      friend std::ostream& operator<<(std::ostream& os, const Vector2& pt) {
        return os << "(" << pt.x << "," << pt.y << ")";
      }
    };

}

#endif // VECTOR_H
