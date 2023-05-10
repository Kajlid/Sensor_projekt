#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

float filteredX = smooth(filteredX, event.acceleration.x);
float filteredY = smooth(filteredY, event.acceleration.y);
float filteredZ = smooth(filteredZ, event.acceleration.z);

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const int buzz = 7;
const int press = A0;

void setup() {
  // put your setup code here, to run once:

  pinMode(press, INPUT);
  pinMode(buzz, OUTPUT);

#ifndef ESP8266
  while (!Serial);    // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

/* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
  
  Serial.println("");

}

void loop() {
  int pressValue = analogRead(press);
  // Serial.println(sensorValue);

/* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
 
  float filteredX = smooth(filteredX, event.acceleration.x);
  float filteredY = smooth(filteredY, event.acceleration.y);
  float filteredZ = smooth(filteredZ, event.acceleration.z);

  String data = "X:" + String(filteredX) + "," + "Y:" + String(filteredY) + "," + "Z:" + String(filteredZ);

  if (pressValue < 50) {
    // Stop the buzzer when the pressure sensor is being "petted"
    delay(100):
    noTone(buzz);
   else {
    if (filteredZ > 0)  {                // if upside down
    Serial.println("angry");           // switch to representing "angry" as int 1?
    tone(buzz, HIGH, 400);
    }

    // add another if statement for when the accelerometer is being shaked quickly
  }
  }


  else  {
    Serial.println(data);
    delay(1000);
  }
}

float smooth(float previous, float new_value){
  const float alpha = 0.8; // Filter coefficient
  float filteredValue = (1 - alpha) * previous + (alpha * new_value);
  return filteredValue;
}
