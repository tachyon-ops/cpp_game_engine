#ifndef ENGINE_PHYSICS_COLLISION_H
#define ENGINE_PHYSICS_COLLISION_H

#include "../Engine.hpp"
#include "../Map/GameMap.hpp"
#include "../Map/TileLayer.hpp"
#include "../common.hpp"
#include <iostream>
#include <vector>

class CollisionHandler {
public:
  bool MapCollision(SDL_Rect a, int tileSize, int RowCount, int ColCount);
  bool CheckCollision(SDL_Rect a, SDL_Rect b);

  void SetCollisionGameLayer(TileLayer *layer);

  inline static CollisionHandler *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
  }

private:
  CollisionHandler();
  TileMap m_CollisionTileMap;
  TileLayer *m_CollisionLayer;
  static CollisionHandler *s_Instance;
};

#endif