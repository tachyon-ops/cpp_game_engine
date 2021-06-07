#ifndef ENGINE_MAP_MAP_PARSER_H
#define ENGINE_MAP_MAP_PARSER_H

// TODO: this include is hugly
#include "../../ThirdParty/tinyxml/tinyxml.h"
#include "GameMap.hpp"
#include "TileLayer.hpp"
#include <map>
#include <string>

class MapParser {
public:
  bool Load(std::string mapID, std::string mapSource);
  void Clean();

  inline GameMap *GetMap(std::string id) { return m_MapDict[id]; };

  inline static MapParser *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
  };

private:
  MapParser(){};
  static MapParser *s_Instance;

  bool Parse(std::string id, std::string source);
  Tileset ParseTileset(TiXmlElement *xmlTileset);
  TileLayer *ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets,
                            int tileSize, int rowCount, int colCount);

  std::map<std::string, GameMap *> m_MapDict;
};

#endif