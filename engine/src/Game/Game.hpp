#ifndef GAME_H
#define GAME_H

#include "../Engine/Engine.hpp"
#include "../Engine/Graphics/TextureManager.hpp"
#include "../Engine/Inputs/Input.hpp"
#include "../Engine/Map/MapParser.hpp"
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

    if (MapParser::GetInstance()->Load()) {
      std::cout << "Failed to load map" << std::endl;
    }

    Game::m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
  };

  /**
   * @brief Render function
   */
  static void Render() {
    if (Game::m_LevelMap != nullptr)
      Game::m_LevelMap->Render();
    player->Draw();
  };

  /**
   * @brief Update function
   */
  static void Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    if (Game::m_LevelMap != nullptr)
      Game::m_LevelMap->Update();
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
  static GameMap *m_LevelMap;
};

GameMap *Game::m_LevelMap = nullptr;
Warrior *Game::player =
    new Warrior(new Properties("player", 100, 300, 200, 200));

#endif