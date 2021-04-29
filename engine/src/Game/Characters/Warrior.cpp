#include "Warrior.hpp"
#include "../../Engine/Engine.hpp"
#include "../../Engine/Graphics/TextureManager.hpp"

Warrior::Warrior(Properties *props) : Character(props) {
  m_RigidBody = new RigidBody();
  m_Animation = new Animation();
  m_Animation->SetProps(props->TextureID, 1, 6, 80, SDL_FLIP_HORIZONTAL);
};

void Warrior::Draw() {
  m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
};

void Warrior::Update(float dt) {
  m_RigidBody->Update(0.1);
  // m_Transform->Log("WARRIOR VEC:");
  m_Transform->TranslateX(m_RigidBody->GetPosition().X);
  m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

  m_Animation->Update();
};

void Warrior::Clean() { TextureManager::GetInstance()->Clean(); };
