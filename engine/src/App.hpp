#include "Engine/Engine.hpp"
#include "Engine/Graphics/TextureManager.hpp"
#include "Engine/Physics/Vector2D.hpp"

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
    Vector2D v1(2, 4), v2(1,1), v3;
    v3 = v1 + v2;
    v1.Log("V1: ");
    v2.Log("V2: ");
    v3.Log("V3: ");
  };

  static void Render() {
    TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465,
                                        Engine::GetInstance()->GetRenderer());
  };
};