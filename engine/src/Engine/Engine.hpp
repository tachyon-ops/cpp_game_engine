#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "Graphics/TextureManager.hpp"
#include "Map/GameMap.hpp"
#include "common.hpp"

// i.e. f_void_t is a type:
// function pointer taking one void argument, returning void
typedef void (*callback)();

class Engine {
public:
  static Engine *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
  };

  bool Init(std::string gameName = "My Game!", callback callback = nullptr);
  bool Clean(callback callback = nullptr);
  void Quit();

  void ShowWindow();

  void Update(callback callback = nullptr);
  void Render(callback callback = nullptr);
  void SetRenderCallback(callback callback = nullptr);
  void Events();

  inline bool IsRunning() { return m_IsRunning; };
  inline SDL_Renderer *GetRenderer() { return m_Renderer; };

private:
  Engine() {
    m_Window = nullptr;
    m_Renderer = nullptr;
    m_firstRun = true;
  };

  static int ResizingEventWatcher(void *data, SDL_Event *event);

  bool m_IsRunning;

  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;

  static Engine *s_Instance;

  bool m_firstRun;
  callback m_render_callback;
};

#endif