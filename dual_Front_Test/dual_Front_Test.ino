//initialize the library with the interface pin numbers
#define lst 5   //left sensor trig
#define lse 4   //left sensor echo
#define frst 10  //right sensor trig
#define frse 2   //right sensor echo
#define flst 6   //front sensor trig
#define flse 7   //front sensor echo

//Proximity flags for ultrasonic sensors
boolean lBlock = false;
boolean fBlock = false;

void setup() {
  Serial.begin (9600);
  pinMode(lst, OUTPUT);
  pinMode(lse, INPUT);
  pinMode(frst, OUTPUT);
  pinMode(frse, INPUT);
  pinMode(flst, OUTPUT);
  pinMode(flse, INPUT);
}

void loop() {
  set_fs();
  if (fBlock == false){
    motor_straight();
  }
  else{
    set_ls();
    if (fBlock == true && lBlock == false){
      motor_left();
    }
	else{
		motor_right();
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
}

void motor_right() {
  digitalWrite(12,HIGH); 
  analogWrite(3,255);
  digitalWrite(13,high);
  analogWrite(11,255);
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
  digitalWrite(frst, LOW);
  delayMicroseconds(2);
  digitalWrite(frst, HIGH);
  delayMicroseconds(10);
  digitalWrite(frst, LOW);
  duration0 = pulseIn(frse, HIGH);
  distance0 = (duration0/2) / 29.1;
  delay(10);
  digitalWrite(flst, LOW);
  delayMicroseconds(2);
  digitalWrite(flst, HIGH);
  delayMicroseconds(10);
  digitalWrite(flst, LOW);
  duration1 = pulseIn(flse, HIGH);
  distance1 = (duration1/2) / 29.1;
  if(distance0 < 20 || distance1 < 20){
    fBlock = true;
  }
  else{
    fBlock = false;
  }
}

