#ifndef FUZZY_CONTROLLER__H
#define FUZZY_CONTROLLER__H

// #include <algorithm>
#include <iostream>
using namespace std;

  static float
  mfTriang(float x, float a, float b, float c);
static float mfTrap(float x, float a, float b, float c, float d);

struct Error {
  float NB, NS, ZE, PS, PB;
};

struct Error_dot {
  float NE, ZE, PO;
};

struct U_dot {
  float NB, NM, NS, ZE, PS, PM, PB;
};

float run_fuzzy(float x1, float x2);
#endif /* FUZZY_CONTROLLER__H */