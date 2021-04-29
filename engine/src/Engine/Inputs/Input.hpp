#ifndef ENGINE_INPUTS_INPUT_H
#define ENGINE_INPUTS_INPUT_H

#include "../common.hpp"

class Input {
public:
  static Input *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new Input();
  };

private:
  Input(){};

  static Input *s_Instance;
};

#endif