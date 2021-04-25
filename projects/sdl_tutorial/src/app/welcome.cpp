#include "welcome.hpp"

void welcome() {
  printf("Welcome to Handmade Hero!\n");

  printf("Starting in %s mode\n", (debug ? "debug" : "production"));
}