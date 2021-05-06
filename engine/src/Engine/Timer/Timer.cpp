#include "Timer.hpp"
#include "../Engine.hpp"
#include "../common.hpp"

Timer *Timer::s_Instance = nullptr;

// https://thenumbat.github.io/cpp-course/sdl2/08/08.html
void Timer::Tick() {
  // Physics loop
  Uint32 current = SDL_GetTicks();
  m_DeltaTime = (current - m_LastTime) * (m_TargetFPS / 1000.0f);
  if (m_DeltaTime > TARGET_DELTATIME) {
    m_DeltaTime = TARGET_DELTATIME;
  }
  m_LastTime = SDL_GetTicks();
};

Timer::Timer() : m_TargetFPS(TARGET_FPS), m_DeltaTime(TARGET_DELTATIME) {
  m_LastTime = SDL_GetTicks();
};