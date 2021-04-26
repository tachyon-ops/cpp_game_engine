#include "Engine.hpp"
#include "common.hpp"

int main() {
  Engine::GetInstance()->Init();
  Engine::GetInstance()->Clean();
  return 0;
}