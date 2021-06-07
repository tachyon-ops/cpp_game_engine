#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "../Physics/Point.hpp"
#include "../Physics/Vector2D.hpp"
#include "../common.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class Camera {
public:
  void Update(float dt);

  static Camera *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
  };

  inline SDL_Rect GetViewBox() { return m_ViewBox; };
  inline Vector2D GetPosition() { return m_Position; };

  inline void SetTarget(Point *target) { m_Target = target; };

private:
  Camera() { m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; };

  Point *m_Target;
  Vector2D m_Position;

  SDL_Rect m_ViewBox;

  static Camera *s_Instance;
};

#endif