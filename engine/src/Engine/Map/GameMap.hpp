#ifndef ENGINE_MAP_GAMEMAP_H
#define ENGINE_MAP_GAMEMAP_H

#include "Layer.hpp"
#include <stdexcept>
#include <stdio.h>
#include <vector>

class GameMap {
public:
  void Render() {
    for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
      m_MapLayers[i]->Render();
    }
  };

  void Update() {
    for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
      m_MapLayers[i]->Update();
    }
  };

  std::vector<Layer *> GetMapLayers() { return m_MapLayers; };

  Layer *GetLayerByName(std::string name) {
    for (Layer *it : m_MapLayers) {
      if (it->GetName() == name) {
        std::cout << "Layer with name " << name << " was found!" << std::endl;
        return it;
      }
    }
    throw std::runtime_error(
        std::string("GameMap::GetLayerByName() no layer with name ") + name);
  };

private:
  friend class MapParser;
  std::vector<Layer *> m_MapLayers;
};

#endif