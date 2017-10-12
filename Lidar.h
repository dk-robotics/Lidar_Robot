#ifndef Lidar_h
#define Lidar_h

#define LIDAR_ADDR_DEFAULT 0x62

#include <Arduino.h>
#include <Wire.h>

class Lidar
{
  public:
      Lidar();
      void begin(bool = true, char = LIDAR_ADDR_DEFAULT);
      void reset();
      void requestDistanceMeassurement(bool = true);
      int getDistance();
      void write(char, char);
      void read(char, int, byte*, bool, char);
};

#endif

