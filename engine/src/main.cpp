#include "Engine/Engine.hpp"
#include "Engine/TextureManager.hpp"

const uint32_t WIN_WIDTH = 800;
const uint32_t WIN_HEIGHT = 600;

void init() {
  TextureManager::GetInstance()->Load("tree", "assets/tree.png",
                                      Engine::GetInstance()->GetRenderer());
}
void render() {
  TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465,
                                      Engine::GetInstance()->GetRenderer());
}

int main(int argc, const char *argv[]) {
  printf("ENGINE TESTING!");

  Engine::GetInstance()->Init(init);

  printf("Engine::GetInstance()->IsRunning(): %s\n",
         Engine::GetInstance()->IsRunning() ? "true" : "false");
  bool firstRun = true;
  while (Engine::GetInstance()->IsRunning()) {
    Engine::GetInstance()->Events();
    Engine::GetInstance()->Update();
    Engine::GetInstance()->Render(render);
    if (firstRun) {
      Engine::GetInstance()->ShowWindow();
      firstRun = false;
    }
  }

  Engine::GetInstance()->Clean();

  return EXIT_SUCCESS;
}