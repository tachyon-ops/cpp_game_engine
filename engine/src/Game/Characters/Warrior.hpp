#ifndef GAME_WARRIOR_H
#define GAME_WARRIOR_H

#include "../../Engine/Animation/Animation.hpp"
#include "../../Engine/Entities/Character.hpp"
#include "../../Engine/Physics/RigidBody.hpp"

class Warrior : public Character {
public:
  Warrior(Properties *props);

  virtual void Draw();
  virtual void Update(float dt = 0.0f);
  virtual void Clean();

private:
  Animation *m_Animation;
  RigidBody *m_RigidBody;
};

#endif