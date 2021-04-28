#ifndef GAME_H
#define GAME_H

#include "../Engine/Engine.hpp"
#include "../Engine/Graphics/TextureManager.hpp"
#include "../Test.hpp"

#include "Characters/Warrior.hpp"

Warrior *player = new Warrior(new Properties("player", 100, 200, 200, 200));

class Game {
public:
  static void Run() {

    Engine::GetInstance()->Init(Game::Init);

    while (Engine::GetInstance()->IsRunning()) {
      Engine::GetInstance()->Events();
      Engine::GetInstance()->Update(Game::Update);
      Engine::GetInstance()->Render(Game::Render);
    }

    Engine::GetInstance()->Clean();
  };

  static void Init() {
    TextureManager::GetInstance()->Load("player",
                                        "assets/Martial Hero/Sprites/Idle.png");
    // TextureManager::GetInstance()->Load("tree", "assets/tree.png");
    // https://youtu.be/m2MDcT89noE?t=1034

    // Test();
  };

  static void Render() {
    SDL_Log("Game::Render callback");
    player->Draw();
    // TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465);
  };

  static void Update() {
    SDL_Log("Game::Update callback, %s", player != nullptr ? "player exists" : "player doesnt exist");
    if (player != nullptr) {
      player->Update(0.0f);
    }
  }
};

#endif