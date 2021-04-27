#ifndef ENGINE_PHYSICS_VECTOR2D_H
#define ENGINE_PHYSICS_VECTOR2D_H

#include <iostream>

// https://youtu.be/pn9oL7mqj1g?t=527
class Vector2D {
public:
  float X, Y;

public:
  Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

public:
  // addition
  inline Vector2D operator+(const Vector2D &v2) const {
    return Vector2D(X + v2.X, Y + v2.Y);
  }

  // subtraction
  inline Vector2D operator-(const Vector2D &v2) const {
    return Vector2D(X - v2.X, Y - v2.Y);
  }

  void Log(std::string msg = "") {
    std::cout << msg << "(X, Y) = (" << X << ", " << Y << ")" << std::endl;
  }
};

#endif