#include <Arduino.h>

// I2C interface by default
//
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

// #define DEBUG 1 in SparkFunLSM303C.h turns on debugging statements.
// Redefine to 0 to turn them off.

LSM303C myIMU;
int north = 13; 

void setup()
{
  Serial.begin(115200);
  if (myIMU.begin() != IMU_SUCCESS)
  {
    Serial.println("Failed setup.");
    while (1);
  }
  pinMode(north, OUTPUT);
  digitalWrite(north, HIGH);
  
}

void loop()
{  Serial.println("\tMagnetometer:\tAccelerometer:");
  Serial.print(" X = \t");
  Serial.print(myIMU.readMagX(), 4);
  Serial.print("\t\t");
  Serial.println(myIMU.readAccelX(), 4);
  Serial.print(" Y = \t");
  Serial.print(myIMU.readMagY(), 4);
  Serial.print("\t\t");
  Serial.println(myIMU.readAccelY(), 4);
  Serial.print(" Z = \t");
  Serial.print(myIMU.readMagZ(), 4);
  Serial.print("\t\t");
  Serial.println(myIMU.readAccelZ(), 4);
//    Serial.print("\nThermometer:\n");
//    Serial.print(" Degrees C = ");
//    Serial.println(myIMU.readTempC(), 4);
//    Serial.print(" Degrees F = ");
//    Serial.println(myIMU.readTempF(), 4);


//compute compass heading
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(myIMU.readMagY(),myIMU.readMagX()) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  if (heading >345 || heading < 15){
    digitalWrite(north, HIGH);
  }
 
  delay(1000);
  digitalWrite(north, LOW);
}
