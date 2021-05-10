#ifndef IPHONE_APP_H
#define IPHONE_APP_H

#include "Engine/Engine.hpp"
#include "Engine/Graphics/TextureManager.hpp"
#include "Engine/Inputs/Input.hpp"
#include "Engine/Timer/Timer.hpp"

class App {
public:
  /**
   * @brief Run function
   */
  static void Run() {
    Engine::GetInstance()->Init("IPhone APP!");
    while (Engine::GetInstance()->IsRunning()) {
      Engine::GetInstance()->Events();
      Engine::GetInstance()->Update();
      Engine::GetInstance()->Render();
      Timer::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();
  };
};

#endif