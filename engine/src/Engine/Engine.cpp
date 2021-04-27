#include "Engine.hpp"
#include <stdlib.h>


Engine *Engine::s_Instance = nullptr;

bool Engine::Init(callback callback) {
  printf("Engine Init!\n");

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to initialize SDL2: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  // https://stackoverflow.com/questions/51643442/sdl2-image-img-init-returns-0-with-img-geterror-being-empty
  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initError = IMG_Init(imgFlags);
  if (initError == imgFlags) {
    std::cout << "SDL_image initialized" << std::endl;
  } else {
    std::cerr << "Failed to initialize SDL_image" << std::endl;
    std::cerr << "Return value: " << initError << std::endl;
    std::cerr << "Error flags: " << IMG_GetError() << std::endl;
    return m_IsRunning = false;
  }

  m_Window = SDL_CreateWindow(
      "Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_METAL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);

  if (m_Window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (m_Renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return m_IsRunning = false;
  }

  // Init callback
  if (callback != nullptr) callback();

  return m_IsRunning = true;
};

void Engine::Update(){
    //
    // SDL_Log("fsafasf");
};

void Engine::ShowWindow() {
  if (m_Window)
    SDL_ShowWindow(m_Window);
}

void Engine::Render(callback callback) {
  SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_Renderer);

  // Callback
  if (callback != nullptr) callback();

  SDL_RenderPresent(m_Renderer);
};

void Engine::Events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    Quit();
    break;
  }
  if (event.type == SDL_QUIT) {
    m_IsRunning = false;
  }
  SDL_Delay(16);
};

bool Engine::Clean() {
  printf("Cleaning... ");
  if (m_Renderer != nullptr) {
    printf("m_Renderer->cleaned! ");
    SDL_DestroyRenderer(m_Renderer);
  }
  if (m_Window != nullptr) {
    printf("m_Window->cleaned! ");
    SDL_DestroyWindow(m_Window);
  }
  // IMG_Quit();
  SDL_Quit();
  printf("\nCleaning done!\n");
  printf("Engine OUT!\n");
  return true;
};

void Engine::Quit() { m_IsRunning = false; };
