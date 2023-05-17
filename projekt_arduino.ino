#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

//sensors_event_t event; 
//accel.getEvent(&event);
// global variables declaration
char val; // Data received from the serial port
float filteredX;         
float filteredY;
float filteredZ;
bool state = true;
/* Get a new sensor event */ 
/*sensors_event_t event; 
accel.getEvent(&event);*/

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
  
  establishContact();  // send a byte to establish contact until receiver responds

}

void pressesing(){
if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val

    if(val == '1') //if we get a 1
    {
       // prosesing ber om data och vi skickar den typ
    }
    delay(100);
  } 
    else {
    // gör ngt annat
    delay(50);
    }

}

void loop() {
  /* Get a new sensor event */ 
    sensors_event_t event; 
    accel.getEvent(&event);
  int pressValue = analogRead(press);
  // Serial.println(sensorValue);
 
  float filteredX = smooth(filteredX, event.acceleration.x);
  float filteredY = smooth(filteredY, event.acceleration.y);
  float filteredZ = smooth(filteredZ, event.acceleration.z);

  String data = "X:" + String(filteredX) + "," + "Y:" + String(filteredY) + "," + "Z:" + String(filteredZ);
  Serial.println(pressValue);
  if (pressValue < 10) {
    // Stop the buzzer when the pressure sensor is being "petted"
    delay(100);
     
    noTone(buzz);
    if (state == false){
      Serial.println("not angry");
      state = true;
    }
  }
  else {
    if (filteredZ > 0 || delta(30, smooth(filteredX, event.acceleration.x),filteredX ) || delta(30, smooth(filteredY, event.acceleration.y),filteredY) )  {                // if upside down
    tone(buzz, HIGH);
    if (state == true){
      Serial.println("angry");
      state = false;
    }
    }


pressesing();

    // add another if statement for when the accelerometer is being shaked quickly
  }




  
}

float smooth(float previous, float new_value){
  const float alpha = 0.7; // Filter coefficient
  float filteredValue = (1 - alpha) * previous + (alpha * new_value);
  return filteredValue;
}




void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }}



bool delta(int cutoff, float variabel, float previus_var){
 float dif = variabel - previus_var;
 if (dif>cutoff){
   return true;
  
 }else{
   return false;
 }

}
