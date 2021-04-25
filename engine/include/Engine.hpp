#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine {
public:
  static Engine *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
  };

  bool Init();
  bool Clean();
  void Quit();

  void ShowWindow();

  void Update();
  void Render();
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