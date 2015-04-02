#include <Servo.h>

Servo servo;

// pins
const int lightSensorPin = 0;
const int servoPin = 9;

// light value
int lightVal = 0;
int prevLightSensorValue = 0;

// arbiatary light level to start waving at
int standardLightLevel = 90;
int minLightLevelDiff = 5;

// waving
boolean waving = false;
int angles[] = {0, 100, 60, 100, 60, 100, 60, 100, 60, 100, 0};
int anglesLength = 11;
int index = 0;

// delay
long previousMillis = 0;
long interval = 500;


// run once
void setup() {
  Serial.begin(9600);
  
  pinMode(lightSensorPin, INPUT);
  
  servo.attach(servoPin);
}


// run forever
void loop() {

  // LIGHT SENSOR
 
  if(waving == false) {
    int lightSensorValue = analogRead(lightSensorPin);
    Serial.println(lightSensorValue);
    if(prevLightSensorValue != 0) {
      int diff = standardLightLevel - lightSensorValue;
      if(diff > minLightLevelDiff) {
        waving = true;
      }
    }
    prevLightSensorValue = lightSensorValue;
  }
 
  // WAVING
  
  if(doInterval() && doWave()) {
    wave();
  }
}

// METHODS
  
boolean doWave() {
  if(waving) {
    if(index < anglesLength) {
      Serial.println(index);
      return true;
    }
    else {
      endWave(); 
    }
  }
  return false;
}

boolean doInterval() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

void wave() {
  Serial.println("wave");
  int servoAngle = angles[index];
  servo.write(servoAngle);
  index++;
}

void endWave() {
  waving = false;
  index = 0;
  delay(2000);
}

