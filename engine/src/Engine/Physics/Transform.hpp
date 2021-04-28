#ifndef ENGINE_PHYSICS_TRANSFORM_H
#define ENGINE_PHYSICS_TRANSFORM_H

#include "Vector2D.hpp"

// https://youtu.be/pn9oL7mqj1g?t=703
class Transform {
public:
  float X, Y;

public:
  Transform(float x = 0, float y = 0) : X(x), Y(y){};

  void Log(std::string msg = "") {
    std::cout << msg << "Transform(X, Y) = (" << X << ", " << Y << ")" << std::endl;
  }

private:
  inline void TranslateX(float x) { X += x; };
  inline void TranslateY(float y) { Y += y; };
  inline void Translate(Vector2D v) { X += v.X; Y += v.Y; };
};

#endif