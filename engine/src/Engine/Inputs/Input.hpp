#ifndef ENGINE_INPUTS_INPUT_H
#define ENGINE_INPUTS_INPUT_H

#include "../common.hpp"

class Input {
public:
  static Input *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
  };

  void Listen();
  bool GetKeyDown(SDL_Scancode key);

private:
  Input();

  void KeyUp();
  void KeyDown();

  const Uint8 *m_KeyStates;

  static Input *s_Instance;
};

#endif