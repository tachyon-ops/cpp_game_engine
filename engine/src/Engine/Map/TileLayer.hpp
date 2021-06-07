#ifndef ENGINE_MAP_TILE_LAYER_H
#define ENGINE_MAP_TILE_LAYER_H

#include "Layer.hpp"
#include <string>
#include <vector>

struct Tileset {
  int FirstID, LastID;
  int RowCount, ColCount;
  int TileCount, TileSize;
  std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;

using IntVectorType = std::vector<int>;     // use only here V please :-)
using TileMap = std::vector<IntVectorType>; // < ------------|

class TileLayer : public Layer {
public:
  TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap,
            TilesetList tilesets, std::string name);

  virtual void Render();
  virtual void Update();

  inline TileMap GetTileMap() { return m_TileMap; };

private:
  int m_TileSize;
  int m_RowCount, m_ColCount;

  TileMap m_TileMap;
  TilesetList m_Tilesets;
};

#endif