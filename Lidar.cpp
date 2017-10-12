#include <Arduino.h>
#include <Wire.h>
#include <stdarg.h>
#include "Lidar.h"

char lidar = LIDAR_ADDR_DEFAULT;

Lidar::Lidar(){}

void Lidar::begin(bool fasti2c, char lidarAddress) {
  lidar = lidarAddress;
  Wire.begin(); // Start I2C
  if(fasti2c) {
    #if ARDUINO >= 157
      Wire.setClock(400000UL); // Set I2C frequency to 400kHz, for Arduino Due
    #else
      TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
    #endif
  }
  
  //Configuration : Short range, high speed + Interrupt on ready
  write(0x02,0x80); // Default
  write(0x04,0x01);
  write(0x1c,0x00); // Default
}

void Lidar::reset() {
  write(0x00,0x00);
}

void Lidar::requestDistanceMeassurement(bool biasCorrection) {
  if(biasCorrection) {
    // Take acquisition & correlation processing with receiver bias correction
    write(0x00,0x04);
  } else {
    // Take acquisition & correlation processing without receiver bias correction
    write(0x00,0x03);
  }
}

/**
This method assumes that the Lidar is not busy!
*/
int Lidar::getDistance() {
  // Array to store high and low bytes of distance
  byte distanceArray[2];
  
  //Testing code
  Wire.beginTransmission((int)lidar);
  Wire.write((int)0x8f); // Set the register to be read
  
  // A nack means the device is not responding, report the error over serial
  int nackCatcher = Wire.endTransmission();
  if(nackCatcher != 0) {
    Serial.println("> nack");
  }
  
  // Perform read of 1 or 2 bytes, save in arrayToSave
  int numOfBytes = 2;
  Wire.requestFrom((int)lidar, numOfBytes);
  int i = 0;
  if(numOfBytes <= Wire.available()) {
    while(i < numOfBytes) {
      distanceArray[i] = Wire.read();
      i++;
    }
  }
  //Testing end
  
  
  // Read two bytes from register 0x8f (autoincrement for reading 0x0f and 0x10)
  //read(0x8f,2,distanceArray,true,lidarliteAddress);
  // Shift high byte and add to low byte
  
  
  int distance = (distanceArray[0] << 8) + distanceArray[1];
  return(distance);
}


void write(char myAddress, char myValue) {
  char lidarliteAddress = lidar;
  Wire.beginTransmission((int)lidarliteAddress);
  Wire.write((int)myAddress); // Set register for write
  Wire.write((int)myValue); // Write myValue to register

  // A nack means the device is not responding, report the error over serial
  int nackCatcher = Wire.endTransmission();
  if(nackCatcher != 0) {
    Serial.println("> nack");
  }

  delay(1); // 1 ms delay for robustness with successive reads and writes
}



//Can probably be deleted
void read(char myAddress, int numOfBytes, byte arrayToSave[2], bool monitorBusyFlag, char lidarliteAddress) {

/**********************************
MY PSEUDO-CODE REPRESENTATION
-----------------------------
bool busyFlag = true; //Lidar is ready for reading when this gets false
int busyCounter = 0; //Check for whether the lidar is hanging

while(busyFlag) {
  set the lidar address to write to
  write(0x01); //Prepare reading register 0x01
  check for nacks...
  read register 0x01
  //if reg 0x01 == 0, then everything is fine, otherwise some error may have occured
  //bit 0 of reg 0x01 is the busyFlag
  busyFlag = input0x01 & 1 != 0 //isolate bit0. Bit0 = 1 when busy, Bit0 = 0 when ready
  
  busyCointer++;
  if(busyCounter > 9999)
    bailout... //The Lidar is hanging somewhere
}

if(!busyFlag) {
  set the lidar address to write to
  write reg //the register to fetch data from
  check for nacks
  
  request read from lidar address, numOfBytesToRead
  int i = 0;
  if(numOfBytesToRead <= Wire.available) {
    while(i < numOfBytesToRead) {
      saveArray[i] = readByte();
      i++;
    }
  }
}

if(bailout) {
  print error;
  restart method...
}

**********************************/
  
  int busyFlag = 0; // busyFlag monitors when the device is done with a measurement
  if(monitorBusyFlag) {
    busyFlag = 1; // Begin read immediately if not monitoring busy flag
  }
  int busyCounter = 0; // busyCounter counts number of times busy flag is checked, for timeout

  while(busyFlag != 0) { // Loop until device is not busy
    // Read status register to check busy flag
    Wire.beginTransmission((int)lidarliteAddress);
    Wire.write(0x01); // Set the status register to be read

    // A nack means the device is not responding, report the error over serial
    int nackCatcher = Wire.endTransmission();
    if(nackCatcher != 0) {
      Serial.println("> nack");
    }

    Wire.requestFrom((int)lidarliteAddress,1); // Read register 0x01
    busyFlag = bitRead(Wire.read(),0); // Assign the LSB of the status register to busyFlag

    busyCounter++; // Increment busyCounter for timeout

    // Handle timeout condition, exit while loop and goto bailout
    if(busyCounter > 9999) {
      goto bailout;
    }
  }

  // Device is not busy, begin read
  if(busyFlag == 0) {
    Wire.beginTransmission((int)lidarliteAddress);
    Wire.write((int)myAddress); // Set the register to be read

    // A nack means the device is not responding, report the error over serial
    int nackCatcher = Wire.endTransmission();
    if(nackCatcher != 0) {
      Serial.println("> nack");
    }

    // Perform read of 1 or 2 bytes, save in arrayToSave
    Wire.requestFrom((int)lidarliteAddress, numOfBytes);
    int i = 0;
    if(numOfBytes <= Wire.available()) {
      while(i < numOfBytes) {
        arrayToSave[i] = Wire.read();
        i++;
      }
    }
  }

  // bailout reports error over serial
  if(busyCounter > 9999) {
    bailout:
      busyCounter = 0;
      Serial.println("> read failed");
  }
}


