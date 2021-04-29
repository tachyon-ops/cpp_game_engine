#ifndef GAME_H
#define GAME_H

#include "../Engine/Engine.hpp"
#include "../Engine/Graphics/TextureManager.hpp"
#include "../Test.hpp"

#include "Characters/Warrior.hpp"

class Game {
public:
  static void Run() {

    Engine::GetInstance()->Init("Warrior Game!", Game::Init);

    while (Engine::GetInstance()->IsRunning()) {
      Engine::GetInstance()->Events();
      Engine::GetInstance()->Update(Game::Update);
      Engine::GetInstance()->Render(Game::Render);
    }

    Engine::GetInstance()->Clean();
  };

  static void Init() {
    // Test();
    TextureManager::GetInstance()->Load("player",
                                        "assets/Martial Hero/Sprites/Idle.png");
  };

  static void Render() { player->Draw(); };

  static void Update() { player->Update(0.0f); }

  static Warrior *player;
};

Warrior *Game::player = new Warrior(new Properties("player", 100, 100, 200, 200));

#endif