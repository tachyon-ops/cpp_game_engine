#include "TileLayer.hpp"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap,
                     TilesetList tilesets)
    : m_Tilesets(tileSize) {

  m_RowCount = rowCount;
  m_ColCount = colCount;
  m_TileMap = tileMap;
  m_Tilesets = tilesets;
};

void TileLayer::Render(){
    //
};

void TileLayer::Update(){
    //
};