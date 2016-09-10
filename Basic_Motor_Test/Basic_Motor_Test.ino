//initialize the library code
#include <LiquidCrystal.h>
//initialize the library with the interface pin numbers
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);
#define lst 5   //left sensor trig
#define lse 4   //left sensor echo
#define rst 10  //right sensor trig
#define rse 2   //right sensor echo
#define fst 6   //front sensor trig
#define fse 7   //front sensor echo

int flag_count = 0;

//Proximity flags for ultrasonic sensors
boolean rBlock = false;
boolean lBlock = false;
boolean fBlock = false;



void setup() {
  //set up lcd's number of columns and rows:
  //lcd.begin(16, 2);
  Serial.begin (9600);
  pinMode(lst, OUTPUT);
  pinMode(lse, INPUT);
  pinMode(rst, OUTPUT);
  pinMode(rse, INPUT);
  pinMode(fst, OUTPUT);
  pinMode(fse, INPUT);

}

void loop() {
  motor_stop();
  set_rs();
  set_fs();

  if (fBlock == false){
    motor_straight();
  }
  else{
    set_ls();
    if (fBlock == true && lBlock == false){
      motor_left();
    }
    if (fBlock == true && lBlock == true){
      set_rs();
      if (rBlock == false){
        motor_right();
      }
      else {
        motor_left();
        motor_left();
      }
    }
  }

}

void motor_straight() {
  digitalWrite(12,HIGH); 
  analogWrite(3,255);
  digitalWrite(13,LOW);
  analogWrite(11,255);
  delay(5000);
}

void motor_right() {
  digitalWrite(12,HIGH); 
  analogWrite(3,255);
  digitalWrite(13,HIGH);
  analogWrite(11,255);
  delay(600);
}

void motor_left() {
  digitalWrite(12,LOW); 
  analogWrite(3,255);
  digitalWrite(13,LOW);
  analogWrite(11,255);
  delay(600);
}

void motor_reverse() {
  digitalWrite(12,LOW); 
  analogWrite(3,255);
  digitalWrite(13,HIGH);
  analogWrite(11,255);
  delay(1000);
}

void motor_stop() { 
  analogWrite(3,0);
  analogWrite(11,0);
}

void set_ls() {
  //lcd.setCursor(0,0);
  long lduration, ldistance;
  digitalWrite(lst, LOW);
  delayMicroseconds(2);
  digitalWrite(lst, HIGH);
  delayMicroseconds(10);
  digitalWrite(lst, LOW);
  lduration = pulseIn(lse, HIGH);
  ldistance = (lduration/2) / 29.1;
  //lcd.print("Left Sensor Reading ");
  //lcd.setCursor(0,1);
  if(ldistance <10){
    //lcd.print("TOO CLOSE!!!");
    lBlock = true;
  }
  else{
    //lcd.print(ldistance);
    //lcd.print(" cm            ");
    lBlock = false;
  }
  delay(100);
}

void set_rs() {
  //lcd.setCursor(0,0);
  long duration, distance;
  digitalWrite(rst, LOW);
  delayMicroseconds(2);
  digitalWrite(rst, HIGH);
  delayMicroseconds(10);
  digitalWrite(rst, LOW);
  duration = pulseIn(rse, HIGH);
  distance = (duration/2) / 29.1;
  //lcd.print("Right Sensor Reading");
  //lcd.setCursor(0,1);
  if(distance <10){
    //lcd.print("TOO CLOSE!!!");
    rBlock = true;
  }
  else{
    //lcd.print(distance);
    //lcd.print(" cm            ");
    rBlock = false;
  }
  delay(100);
}

void set_fs() {
  //lcd.setCursor(0,0);
  long duration, distance;
  digitalWrite(fst, LOW);
  delayMicroseconds(2);
  digitalWrite(fst, HIGH);
  delayMicroseconds(10);
  digitalWrite(fst, LOW);
  duration = pulseIn(fse, HIGH);
  distance = (duration/2) / 29.1;
  //lcd.print("Front Sensor Reading");
  //lcd.setCursor(0,1);
  if(distance <10){
    //lcd.print("TOO CLOSE!!!");
    fBlock = true;
  }
  else{
    //lcd.print(distance);
    //lcd.print(" cm            ");
    fBlock = false;
  }
  delay(100);
}

