#include "TextureManager.hpp"
#include <stdlib.h>

TextureManager *TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename,
                          SDL_Renderer *renderer) {
  SDL_Surface *surface = IMG_Load(filename.c_str());

  if (surface == nullptr) {
    SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
    return false;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == nullptr) {
    SDL_Log("Failed to load texture from surface: %s, %s", filename.c_str(),
            SDL_GetError());
    return false;
  }

  m_TextureMap[id] = texture;

  return true;
};

void TextureManager::Draw(std::string id, int x, int y, int width, int height,
                          SDL_Renderer *renderer, SDL_RendererFlip flip) {
  SDL_Rect srcRect = {0, 0, width, height};
  SDL_Rect dstRect = {x, y, width, height};
  SDL_RenderCopyEx(renderer, m_TextureMap[id], &srcRect, &dstRect, 0, nullptr,
                   flip);
};

void TextureManager::Drop(std::string id){
    //
};

void TextureManager::Clean(){};
