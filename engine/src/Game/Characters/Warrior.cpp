#include "Warrior.hpp"
#include "../../Engine/Engine.hpp"
#include "../../Engine/Graphics/TextureManager.hpp"
#include "../../Engine/Inputs/Input.hpp"

Warrior::Warrior(Properties *props) : Character(props) {
  m_RigidBody = new RigidBody();
  m_Animation = new Animation();
  m_Animation->SetProps(props->TextureID, 1, 6, 80);
};

void Warrior::Draw() {
  m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
};

void Warrior::Update(float dt) {
  m_Animation->SetProps(m_TextureID, 1, 6, 120, m_Flip);
  m_RigidBody->UnsetForce();

  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
    m_Flip = SDL_FLIP_HORIZONTAL;
    m_Animation->SetProps("player_run", 1, 6, 80, m_Flip);
    m_RigidBody->ApplyForceX(5 * BACKWARD);
  }

  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
    m_Flip = SDL_FLIP_NONE;
    m_Animation->SetProps("player_run", 1, 6, 80, m_Flip);
    m_RigidBody->ApplyForceX(5 * FORWARD);
  }

  m_RigidBody->Update(0.8);

  // SDL_Log("%f", dt);
  // m_Transform->Log("WARRIOR VEC:");
  m_Transform->TranslateX(m_RigidBody->GetPosition().X);
  // m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

  m_Animation->Update();
};

void Warrior::Clean() { TextureManager::GetInstance()->Clean(); };
