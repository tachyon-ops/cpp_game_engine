#include "Engine.hpp"

int main() {
  Engine::GetInstance()->Init();
  Engine::GetInstance()->Clean();
  return 0;
}