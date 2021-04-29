#include "Animation.hpp"
#include "../Graphics/TextureManager.hpp"

void Animation::Update() {
  if (m_FrameCount == 0) {
    SDL_Log("m_FrameCount of %s is ZERO! That cannot be!", m_TextureID.c_str());
  }
  m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
};

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
  TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth,
                                           spriteHeight, m_SpriteRow,
                                           m_SpriteFrame, m_Flip);
};

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount,
                         int animSpeed, SDL_RendererFlip flip) {
  m_TextureID = textureID;
  m_SpriteRow = spriteRow;
  m_FrameCount = frameCount;
  m_AnimSpeed = animSpeed;
  m_Flip = flip;
};