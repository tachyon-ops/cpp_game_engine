#include "Engine/Engine.hpp"
#include "Engine/Graphics/TextureManager.hpp"

class App {
  public:
  static void Run() {
    Engine::GetInstance()->Init(App::Init);

    while (Engine::GetInstance()->IsRunning()) {
      Engine::GetInstance()->Events();
      Engine::GetInstance()->Update();
      Engine::GetInstance()->Render(App::Render);
    }

    Engine::GetInstance()->Clean();
  };

  static void Init() {
    TextureManager::GetInstance()->Load("tree", "assets/tree.png",
                                        Engine::GetInstance()->GetRenderer());
  };

  static void Render() {
    TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465,
                                        Engine::GetInstance()->GetRenderer());
  };
};