//initialize the library with the interface pin numbers
#include <IRremote.h>

#define lst 6   //left sensor trig
#define lse 7   //left sensor echo
#define frst 1  //front right sensor trig
#define frse 2   //front right sensor echo
#define flst 5   //front left sensor trig
#define flse 4   //front left sensor echo
#define fmst 8   //front mid sensor trig
#define fmse 9   //front mid sensor echo
#define irfs 23  //front IR reciever

//Proximity flags for ultrasonic sensors
boolean lBlock = false;
boolean fBlock = false;

//IR pin assignment and variables
IRrecv irrecv(irfs); //create an IRrecv object
decode_results decodedSignal; //stores results from IR detector

void setup() {
  pinMode(lst, OUTPUT);
  pinMode(lse, INPUT);
  pinMode(frst, OUTPUT);
  pinMode(frse, INPUT);
  pinMode(flst, OUTPUT);
  pinMode(flse, INPUT);
  pinMode(fmst, OUTPUT);
  pinMode(fmse, INPUT);
  pinMode(irfs, INPUT);
  irrecv.enableIRIn();
}

void loop() {
  do{
    set_fs();
    if (fBlock == false){
      motor_straight();
    }
    else{
      set_fs();
      set_ls();
      if (fBlock == true && lBlock == false){
        motor_left();
      }
      else{
        do{
          set_fs();
          motor_right();
        } while (fBlock == true);
      }
    }
  }while (irrecv.decode(&decodedSignal) == false);
    docking();
}

void motor_straight() {
  digitalWrite(12,HIGH); 
  analogWrite(3,255);
  digitalWrite(13,LOW);
  analogWrite(11,230);
}

void motor_straight_slow() {
  digitalWrite(12,HIGH); 
  analogWrite(3,150);
  digitalWrite(13,LOW);
  analogWrite(11,150);
}

void motor_left() {
  digitalWrite(12,LOW); 
  analogWrite(3,200);
  digitalWrite(13,LOW);
  analogWrite(11,200);
}

void motor_right() {
  digitalWrite(12,HIGH); 
  analogWrite(3,200);
  digitalWrite(13,HIGH);
  analogWrite(11,200);
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
  if(ldistance < 40){
    lBlock = true;
  }
  else{
    lBlock = false;
  }
}

void set_fs() {
  irrecv.resume();
  long duration0, distance0;
  long duration1, distance1;
  long duration2, distance2;
  digitalWrite(frst, LOW);
  delayMicroseconds(2);
  digitalWrite(frst, HIGH);
  delayMicroseconds(10);
  digitalWrite(frst, LOW);
  duration0 = pulseIn(frse, HIGH);
  distance0 = (duration0/2) / 29.1;
  delay(10);
  digitalWrite(fmst, LOW);
  delayMicroseconds(2);
  digitalWrite(fmst, HIGH);
  delayMicroseconds(10);
  digitalWrite(fmst, LOW);
  duration1 = pulseIn(fmse, HIGH);
  distance1 = (duration1/2) / 29.1;
  delay(10);
  digitalWrite(flst, LOW);
  delayMicroseconds(2);
  digitalWrite(flst, HIGH);
  delayMicroseconds(10);
  digitalWrite(flst, LOW);
  duration2 = pulseIn(flse, HIGH);
  distance2 = (duration2/2) / 29.1;
  if(distance0 < 40 || distance1 < 40 || distance2 < 40){
    fBlock = true;
  }
  else{
    fBlock = false;
  }
}

void docking() {
  long duration0, distance0;
  long duration2, distance2;
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
  duration2 = pulseIn(flse, HIGH);
  distance2 = (duration2/2) / 29.1;
  if (distance0 > distance2){
      motor_left();
    }
  else if (distance0 < distance2){
    motor_right();
  }
  else{
    if (distance0 <= 10){
      motor_stop();
    }
    else{
        motor_straight_slow();  
    }
  }
}

