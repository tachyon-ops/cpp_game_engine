#include "Warrior.hpp"
#include "../../Engine/Camera/Camera.hpp"
#include "../../Engine/Engine.hpp"
#include "../../Engine/Graphics/TextureManager.hpp"
#include "../../Engine/Inputs/Input.hpp"
#include "../../Engine/Physics/CollisionHandler.hpp"

Warrior::Warrior(Properties *props) : Character(props) {

  m_JumpTime = JUMP_TIME;
  m_JumpForce = JUMP_FORCE;

  m_Collider = new Collider();
  m_Collider->SetBuffer(-80, -60, 160, 175);

  m_RigidBody = new RigidBody();
  m_RigidBody->SetGravity(3.0f);

  m_Animation = new Animation();
  m_Animation->SetProps(props->TextureID, 1, 6, 80);
};

void Warrior::Draw() {
  m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

  Vector2D cam = Camera::GetInstance()->GetPosition();
  SDL_Rect box = m_Collider->Get();
  box.x -= cam.X;
  box.y -= cam.Y;
  SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
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

  // Jump
  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
    m_IsJumping = true;
    m_IsGrounded = false;
    m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
  }
  if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping &&
      m_JumpTime > 0) {
    m_JumpTime -= dt;
    m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
  } else {
    m_IsJumping = false;
    m_JumpTime = JUMP_TIME;
  }

  m_RigidBody->Update(dt);

  // SDL_Log("%f", dt);

  // move on the X axis
  m_RigidBody->Update(dt * RATIO);
  m_LastSafePosition.X = m_Transform->X;
  m_Transform->X += m_RigidBody->GetPosition().X;
  m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

  if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get(), 32, 20,
                                                    60)) {
    m_Transform->X = m_LastSafePosition.X;
  }

  // move on Y axis
  m_RigidBody->Update(dt);
  m_LastSafePosition.Y = m_Transform->Y;
  m_Transform->Y += m_RigidBody->GetPosition().Y;
  m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

  if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get(), 32, 20,
                                                    60)) {
    m_IsGrounded = true;
    m_Transform->Y = m_LastSafePosition.Y;
  } else {
    m_IsGrounded = false;
  }

  m_Origin->X = m_Transform->X + m_Width / 2;
  m_Origin->Y = m_Transform->Y + m_Height / 2;

  m_Animation->Update();
};

void Warrior::Clean() { TextureManager::GetInstance()->Clean(); };
