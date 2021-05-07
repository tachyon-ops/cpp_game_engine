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
  bool Load();
  void Clean();

  // inline GameMap GetMaps() { return m_MapDict; };
  inline std::map<std::string, GameMap *> GetMaps() { return m_MapDict; };

  inline static MapParser *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
  };

private:
  MapParser(){};
  static MapParser *s_Instance;

  bool Parse(std::string id, std::string source);
  Tileset PaserTileset(TiXmlElement *xmlTileset);
  TileLayer *ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets,
                            int tileSize, int rowCount, int colCount);

  std::map<std::string, GameMap *> m_MapDict;
};

#endif