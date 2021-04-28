#include "Warrior.hpp"
#include "../../Engine/Engine.hpp"
#include "../../Engine/Graphics/TextureManager.hpp"

Warrior::Warrior(Properties *props) : Character(props) {
  m_Row = 1;
  m_FrameCount = 0;
  m_AnimSpeed = 80;
};

void Warrior::Draw() {
  TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X,
                                           m_Transform->Y, m_Width, m_Height,
                                           m_Row, m_Frame);
};

void Warrior::Update(float dt = 0.0f) {
  int ticks = SDL_GetTicks() / m_AnimSpeed;
  SDL_Log("Warrior update %u", ticks);
  // TODO: fix this floating point exception!
  // https://youtu.be/m2MDcT89noE?t=1109
  // m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
};

void Warrior::Clean() { TextureManager::GetInstance()->Clean(); };
