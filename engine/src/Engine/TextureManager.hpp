#ifndef ENGINE_TEXTUREMANAGER_H
#define ENGINE_TEXTUREMANAGER_H

#include "common.hpp"

class TextureManager {
public:
  static TextureManager *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new TextureManager();
  };

  bool Load(std::string id, std::string filename, SDL_Renderer *renderer);
  void Drop(std::string id);
  void Clean();

  void Draw(std::string id, int x, int y, int width, int height,
            SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
  TextureManager(){};

  std::map<std::string, SDL_Texture *> m_TextureMap; // { id, *texture }
  static TextureManager *s_Instance;
};

#endif