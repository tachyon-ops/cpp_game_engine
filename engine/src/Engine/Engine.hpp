#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "common.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

// i.e. f_void_t is a type:
// function pointer taking one void argument, returning void
typedef void (*callback)();
// void callback(){};

class Engine {
public:
  static Engine *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
  };

  bool Init(callback f = nullptr);
  bool Clean();
  void Quit();

  void ShowWindow();

  void Update();
  void Render(callback f = nullptr);
  void Events();

  inline bool IsRunning() { return m_IsRunning; };
  inline SDL_Renderer *GetRenderer() { return m_Renderer; };

private:
  Engine() {
    m_Window = nullptr;
    m_Renderer = nullptr;
  };

  bool m_IsRunning;

  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;

  static Engine *s_Instance;
};

#endif