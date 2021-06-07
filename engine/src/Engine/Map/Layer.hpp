#ifndef ENGINE_MAP_LAYER_H
#define ENGINE_MAP_LAYER_H

#include <string>
class Layer {
public:
  Layer(std::string name) { m_Name = name; };

  virtual void Render() = 0;

  virtual void Update() = 0;

  virtual std::string GetName() { return m_Name; };

protected:
  std::string m_Name;
};

#endif