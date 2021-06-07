#ifndef ENGINE_PHYSICS_POINT_H
#define ENGINE_PHYSICS_POINT_H

#include <iostream>

class Point {
public:
  float X, Y;

  Point(float X = 0, float Y = 0) : X(X), Y(Y){};

  // addition +
  inline Point operator+(const Point &p2) { return Point(X + p2.X, Y + p2.Y); };

  // addition +=
  inline friend Point operator+=(Point &p1, const Point &p2) {
    p1.X += p2.X;
    p1.Y += p2.Y;
    return p1;
  };

  // subtraction
  inline Point operator-(const Point &p2) { return Point(X - p2.X, Y - p2.Y); };

  // subtraction -=
  inline friend Point operator-=(Point &p1, const Point &p2) {
    p1.X -= p2.X;
    p1.Y -= p2.Y;
    return p1;
  };

  // multiplication
  inline Point operator*(const float scalar) {
    return Point(X * scalar, Y * scalar);
  };

  void Log(std::string msg = "") {
    std::cout << msg << "(X, Y) = (" << X << ", " << Y << ")" << std::endl;
  }
};

#endif