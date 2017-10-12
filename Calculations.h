#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>

struct Point {
  float x;
  float y;
};

class Calculations {
  public:
      Calculations();
      void addPoint(Point*);
};

#endif

