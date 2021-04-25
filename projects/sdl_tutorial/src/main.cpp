#include "Engine.hpp"
#include "app/welcome.hpp"

const uint32_t WIN_WIDTH = 800;
const uint32_t WIN_HEIGHT = 600;

int main(int argc, const char *argv[]) {
  welcome();

  Engine::GetInstance()->Init();

  printf("Engine::GetInstance()->IsRunning(): %s\n",
         Engine::GetInstance()->IsRunning() ? "true" : "false");
  bool firstRun = true;
  while (Engine::GetInstance()->IsRunning()) {
    Engine::GetInstance()->Events();
    Engine::GetInstance()->Update();
    Engine::GetInstance()->Render();
    if (firstRun) {
      Engine::GetInstance()->ShowWindow();
      firstRun = false;
    }
  }

  Engine::GetInstance()->Clean();

  return EXIT_SUCCESS;
}