#ifndef ENGINE_TIMER_TIMER_H
#define ENGINE_TIMER_TIMER_H

#include "../common.hpp"

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
public:
  void Tick();

  inline float GetDeltaTime() { return m_DeltaTime; };

  // TargetFPS setter and getter
  inline float GetTargetFPS() { return m_TargetFPS; };
  void SetTargetFPS(float targetFPS = TARGET_FPS) { m_TargetFPS = targetFPS; };

  inline static Timer *GetInstance() {
    return (s_Instance != nullptr) ? s_Instance : new Timer();
  };

private:
  Timer();

  void RenderText(std::string text, SDL_Rect dest);

  static Timer *s_Instance;

  float m_TargetFPS;

  float m_DeltaTime;
  Uint32 m_LastTime;
};

#endif