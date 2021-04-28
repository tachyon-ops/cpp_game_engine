#ifndef ENGINE_CHARACTER_H
#define ENGINE_CHARACTER_H

#include "../Object/GameObject.hpp"
#include <string>

class Character : public GameObject {
public:
  Character(Properties *props) : GameObject(props) {}

  virtual void Draw() = 0;
  virtual void Update(float dt) = 0;
  virtual void Clean() = 0;

protected:
  std::string m_Name;
};

#endif