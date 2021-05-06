#ifndef ENGINE_MAP_GAMEMAP_H
#define ENGINE_MAP_GAMEMAP_H

#include "Layer.hpp"
#include <vector>

using MapLayersType = std::vector<Layer *>;

class GameMap {
public:
  void Render() {
    for (unsigned int i = 0; i < m_Map_Layers.size(); i++) {
      m_Map_Layers[i]->Render();
    }
  };

  void Update() {
    for (unsigned int i = 0; i < m_Map_Layers.size(); i++) {
      m_Map_Layers[i]->Update();
    }
  };

  MapLayersType GerMapLayers() { return m_Map_Layers; };

private:
  MapLayersType m_Map_Layers;
};

#endif