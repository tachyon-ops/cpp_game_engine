#ifndef GAME_H
#define GAME_H

#include "../Engine/Engine.hpp"
#include "../Engine/Graphics/TextureManager.hpp"
#include "../Engine/Inputs/Input.hpp"
#include "../Engine/Timer/Timer.hpp"
#include "../Test.hpp"

#include "Characters/Warrior.hpp"

class Game {
public:
  /**
   * @brief Init function
   */
  static void Init() {
    // Test();
    TextureManager::GetInstance()->Load("player",
                                        "assets/Martial Hero/Sprites/Idle.png");
    TextureManager::GetInstance()->Load("player_run",
                                        "assets/Martial Hero/Sprites/Run.png");
  };

  /**
   * @brief Render function
   */
  static void Render() { player->Draw(); };

  /**
   * @brief Update function
   */
  static void Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
  }

  /**
   * @brief Run function
   */
  static void Run() {
    Engine::GetInstance()->Init("Warrior Game!", Game::Init);
    while (Engine::GetInstance()->IsRunning()) {
      Engine::GetInstance()->Events();
      Engine::GetInstance()->Update(Game::Update);
      Engine::GetInstance()->Render(Game::Render);
      Timer::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();
  };

  /**
   * @brief Warrior!
   *
   */
  static Warrior *player;
};

Warrior *Game::player =
    new Warrior(new Properties("player", 100, 300, 200, 200));

#endif