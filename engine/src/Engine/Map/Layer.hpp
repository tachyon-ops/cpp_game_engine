#ifndef ENGINE_MAP_LAYER_H
#define ENGINE_MAP_LAYER_H

class Layer {
public:
  virtual void Render() = 0;

  virtual void Update() = 0;
};

#endif