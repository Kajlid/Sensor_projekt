/* initiate variables */
int bluepin = 6;
int greenpin = 5;
int redpin = 4;
int magnetpin = 2;
int ldrpin = 5;

int mill;
int start;
int scared;
int angry;
int seconds_ldr = 0;
int seconds_magnet = 0;
//int first = 0;

void setup() {
  /* set up pins, start serial */
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(magnetpin, INPUT);
  pinMode(ldrpin, INPUT);
  Serial.begin(9600);

  /* begin the "emotions" on the first run, set start time */
  digitalWrite(greenpin, HIGH);
  /* Assume 1 = False, 0 = True*/ 
  scared = 1;
  angry = 1;
  start = millis();
}

void loop() {

  /*Read values*/
  mill = millis();
  int ldrvalue = analogRead(ldrpin);
  int magnetvalue = digitalRead(magnetpin);
  //Serial.println(mill);
  //Serial.println(ldrvalue);
  delay(100);
  //int redvalue = digitalRead(redpin);

  // --------------- Scared (LDR-sensor) ------------------------
  /* check how long pet is being scared for */
  if (ldrvalue<=15){
    seconds_ldr += millis();
  }
  /* Reset if not continuous */
  if (ldrvalue >= 40){
    seconds_ldr = 0;
  }
  
  /* if pet has been scared, show scared (blue) and send to other node */
  if (seconds_ldr >= 5000){
    seconds_ldr = 0;
    scared = 0;
    //mill = millis();
    // skicka scared till annan nod!
    digitalWrite(greenpin, LOW);
    digitalWrite(bluepin, HIGH);
  }

  // --------------- Scared (LDR-sensor) end ------------------------

  // --------------- Instead of getting data from other node (test) --------------- 
  if(mill-start >= 10000){
    angry = 0;
    mill = 0;
    start = 0;
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, HIGH);
  }
  // --------------- End (test)---------------------------------------------

  // --------------- Pacified (Magnet-sensor) ------------------------
  
  /* check how long pet has been "pacified" */
  if (magnetvalue==HIGH){
    seconds_magnet += millis();
  }
  /* Reset if not continuous */
  if (magnetvalue == LOW){
    seconds_magnet = 0;
  }

  /* if pacified, become happy (green) */
  if (seconds_magnet >= 5000){
    seconds_magnet = 0;
    angry = 1;
    scared = 1;
    digitalWrite(redpin, LOW);
    digitalWrite(bluepin, LOW);
    digitalWrite(greenpin, HIGH);
  }
  // --------------- Pacified (Magnet-sensor) end ------------------------
}