#include "Engine.hpp"
#include "Inputs/Input.hpp"
#include <stdlib.h>

Engine *Engine::s_Instance = nullptr;

/**
 * @impNote in the future, we might want to bullet proof this with an image
 * ratio https://www.javaer101.com/en/article/12981125.html
 */
// int Engine::ResizingEventWatcher(void *data, SDL_Event *event) {
//   if (event->type == SDL_WINDOWEVENT &&
//       event->window.event == SDL_WINDOWEVENT_RESIZED) {
//     SDL_Window *win = SDL_GetWindowFromID(event->window.windowID);
//     if (win == (SDL_Window *)data) {
//       // Engine::GetInstance()->Render();
//     }
//   }
//   return 0;
// }

bool Engine::Init(std::string gameName, callback callback) {
  SDL_Log("Engine initializing!");

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL2: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  // https://stackoverflow.com/questions/51643442/sdl2-image-img-init-returns-0-with-img-geterror-being-empty
  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initError = IMG_Init(imgFlags);
  if (initError == imgFlags) {
    SDL_Log("Image system initialized!");
  } else {
    SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
    return m_IsRunning = false;
  }

  if (TTF_Init() != 0) {
    SDL_Log("Error initializing SDL_ttf: %s", TTF_GetError());
    return m_IsRunning = false;
  } else {
    SDL_Log("Font system initialized!");
  }

  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_METAL | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI);
  m_Window = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, window_flags);
  if (m_Window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  // Add resizing event watch
  // SDL_AddEventWatch(Engine::ResizingEventWatcher, m_Window);

  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_Renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  // Init callback
  if (callback != nullptr)
    callback();

  SDL_Log("Engine initialized!");
  return m_IsRunning = true;
};

void Engine::Update(callback callback) {
  // SDL_Log("Engine updating");
  if (callback != nullptr && m_firstRun == false) {
    // SDL_Log("Engine updating callback!");
    callback();
  }
};

void Engine::ShowWindow() {
  if (m_Window)
    SDL_ShowWindow(m_Window);
}

void Engine::SetRenderCallback(callback callback) {
  m_render_callback = callback;
}

void Engine::Render(callback callback) {
  SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_Renderer);

  // Callback
  if (callback != nullptr) {
    Engine::SetRenderCallback(callback);
    callback();
  } else if (m_render_callback != nullptr) {
    m_render_callback();
  }

  SDL_RenderPresent(m_Renderer);

  if (m_firstRun) {
    Engine::GetInstance()->ShowWindow();
    m_firstRun = false;
  }
};

void Engine::Events() { Input::GetInstance()->Listen(); };

bool Engine::Clean(callback callback) {
  SDL_Log("Cleaning...");

  // Callback
  if (callback != nullptr)
    callback();

  TextureManager::GetInstance()->Clean();

  if (m_Renderer != nullptr) {
    SDL_Log("m_Renderer->cleaned!");
    SDL_DestroyRenderer(m_Renderer);
  }
  if (m_Window != nullptr) {
    SDL_Log("m_Window->cleaned!");
    SDL_DestroyWindow(m_Window);
  }
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Cleaning done!");
  SDL_Log("Engine OUT!");
  return true;
};

void Engine::Quit() { m_IsRunning = false; };
