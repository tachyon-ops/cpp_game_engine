#ifndef TEST_H
#define TEST_H

#include "Engine/Physics/Transform.hpp"
#include "Engine/Physics/Vector2D.hpp"
#include "Engine/common.hpp"

void Test() {
  printf("Testing everything");

  Vector2D v1(2, 4), v2(1, 1), v3;
  v3 = v1 + v2;
  v1.Log("V1: ");
  v2.Log("V2: ");
  v3.Log("V3: ");

  Transform tf;
  tf.Log();
}

#endif