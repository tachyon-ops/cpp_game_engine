#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "common.hpp"

class TextureManager {
public:
  static TextureManager *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new TextureManager();
  };

  bool Load(std::string id, std::string filename);
  void Drop(std::string id);
  void Clean();

  void Draw(std::string id, int x, int y, int width, int height,
            SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
  TextureManager();

  static TextureManager *s_Instance;
};

#endif