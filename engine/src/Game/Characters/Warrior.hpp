#ifndef GAME_WARRIOR_H
#define GAME_WARRIOR_H

#include "../../Engine/Animation/Animation.hpp"
#include "../../Engine/Entities/Character.hpp"
#include "../../Engine/Physics/RigidBody.hpp"
#include "../../Engine/Physics/Collider.hpp"
#include "../../Engine/Physics/Vector2D.hpp"

#define JUMP_TIME 15.0f
#define JUMP_FORCE -10.0f
#define RATIO 0.5f
class Warrior : public Character {
public:
  Warrior(Properties *props);

  virtual void Draw();
  virtual void Update(float dt = 0.0f);
  virtual void Clean();

private:
  bool m_IsJumping;
  bool m_IsGrounded;

  float m_JumpTime;
  float m_JumpForce;

  Collider* m_Collider;
  Vector2D m_LastSafePosition;

  Animation *m_Animation;
  RigidBody *m_RigidBody;
};

#endif