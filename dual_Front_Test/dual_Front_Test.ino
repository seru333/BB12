//initialize the library with the interface pin numbers
#define lst 5   //left sensor trig
#define lse 4   //left sensor echo
#define rst 10  //right sensor trig
#define rse 2   //right sensor echo
#define fst 6   //front sensor trig
#define fse 7   //front sensor echo

//Proximity flags for ultrasonic sensors
boolean lBlock = false;
boolean fBlock = false;

void setup() {
  Serial.begin (9600);
  pinMode(lst, OUTPUT);
  pinMode(lse, INPUT);
  pinMode(rst, OUTPUT);
  pinMode(rse, INPUT);
  pinMode(fst, OUTPUT);
  pinMode(fse, INPUT);

}

void loop() {
  set_fs();

  if (fBlock == false){
    motor_straight();
  }
  else{
    
    //motor_stop();
    set_ls();
    if (fBlock == true && lBlock == false){
      motor_left();
    }
  }

}

void motor_straight() {
  digitalWrite(12,HIGH); 
  analogWrite(3,255);
  digitalWrite(13,LOW);
  analogWrite(11,250);
}

void motor_left() {
  digitalWrite(12,LOW); 
  analogWrite(3,255);
  digitalWrite(13,LOW);
  analogWrite(11,255);
  //delay(850);
}

void motor_stop() { 
  analogWrite(3,0);
  analogWrite(11,0);
}

void set_ls() {
  long lduration, ldistance;
  digitalWrite(lst, LOW);
  delayMicroseconds(2);
  digitalWrite(lst, HIGH);
  delayMicroseconds(10);
  digitalWrite(lst, LOW);
  lduration = pulseIn(lse, HIGH);
  ldistance = (lduration/2) / 29.1;
  if(ldistance <25){
    lBlock = true;
  }
  else{
    lBlock = false;
  }
}

void set_fs() {
  long duration0, distance0;
  long duration1, distance1;
  digitalWrite(rst, LOW);
  delayMicroseconds(2);
  digitalWrite(rst, HIGH);
  delayMicroseconds(10);
  digitalWrite(rst, LOW);
  duration0 = pulseIn(rse, HIGH);
  distance0 = (duration0/2) / 29.1;
  delay(10);
  digitalWrite(fst, LOW);
  delayMicroseconds(2);
  digitalWrite(fst, HIGH);
  delayMicroseconds(10);
  digitalWrite(fst, LOW);
  duration1 = pulseIn(fse, HIGH);
  distance1 = (duration1/2) / 29.1;
  if(distance0 < 20 || distance1 < 20){
    fBlock = true;
  }
  else{
    fBlock = false;
  }
}

