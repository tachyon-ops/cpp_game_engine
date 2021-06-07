#include "MapParser.hpp"

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load(std::string id, std::string source) {
  return Parse(id, source);
};

bool MapParser::Parse(std::string id, std::string source) {
  TiXmlDocument xml;
  xml.LoadFile(source);
  if (xml.Error()) {
    std::cerr << "Failed to load : " << source << std::endl;
    return false;
  }

  TiXmlElement *root = xml.RootElement();

  int rowCount, colCount, tileSize = 0;

  root->Attribute("width", &colCount);
  root->Attribute("height", &rowCount);
  root->Attribute("tileswidth", &tileSize);

  // Parse tilesets
  TilesetList tilesets;
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("tileset")) {
      tilesets.push_back(ParseTileset(e));
    }
  }

  // Parse Layers
  GameMap *gamemap = new GameMap();
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("layer")) {
      TileLayer *tileLayer =
          ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
      gamemap->m_MapLayers.push_back(tileLayer);
    }
  }

  m_MapDict[id] = gamemap;
  return true;
};

Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset) {
  Tileset tileset;
  tileset.Name = xmlTileset->Attribute("name");
  xmlTileset->Attribute("firstgid", &tileset.FirstID);

  xmlTileset->Attribute("tilecount", &tileset.TileCount);
  tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

  xmlTileset->Attribute("columns", &tileset.ColCount);
  tileset.RowCount = tileset.TileCount / tileset.ColCount;
  xmlTileset->Attribute("tilewidth", &tileset.TileSize);

  TiXmlElement *image = xmlTileset->FirstChildElement();
  tileset.Source = image->Attribute("source");
  return tileset;
};

TileLayer *MapParser::ParseTileLayer(TiXmlElement *xmlLayer,
                                     TilesetList tilesets, int tileSize,
                                     int rowCount, int colCount) {
  TiXmlElement *data;
  for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("data")) {
      data = e;
      break;
    }
  }

  // Parese Layer Tile Map
  std::string matrix(data->GetText());
  std::istringstream iss(matrix);
  std::string id;

  TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

  for (int row = 0; row < rowCount; row++) {
    for (int col = 0; col < colCount; col++) {
      getline(iss, id, ',');
      std::stringstream converter(id);
      converter >> tileMap[row][col];

      if (!iss.good()) {
        break;
      }
    }
  }

  return new TileLayer(tileSize, rowCount, colCount, tileMap, tilesets,
                       xmlLayer->Attribute("name"));
};

void MapParser::Clean() {
  std::map<std::string, GameMap *>::iterator it;
  for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
    it->second = nullptr;
  }
  m_MapDict.clear();
};