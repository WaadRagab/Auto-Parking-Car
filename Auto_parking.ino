#include <ESP32Servo.h>
Servo servoFront;
//Back sensor
#define trigPinBack 12
#define echoPin1 34
//Front sensor
#define trigPin 33
#define echoPin2 35
//Enable to control the speed
#define en 25
// Motor A
#define in1  13
#define in2  14
// Motor B
#define in3  26
#define in4 27
//Control the speed
#define S 60 
//Define function
void forward();
void backward();
void right();
void left();
void Stop();
int UFun(int triger,int echo);
void Park();
int Find_slot();
//bool Objects_to_avoid();

void setup() {
  Serial.begin(9600);
  pinMode(en, OUTPUT);
  servoFront.attach(32);
  analogWrite(en, S);
  pinMode(trigPin,OUTPUT);
  pinMode(trigPinBack,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(echoPin2,INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() 
{
 
 servoFront.write(0);
  find_slot();
  Stop();
  Park();
  Stop();
  while(1){} 

}

void forward() {  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward(){
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
   }


int UFun(int triger , int echo){
   long duration ;
   int distance;
   digitalWrite(triger,LOW);
   delayMicroseconds(2);
   digitalWrite(triger, HIGH);
   delayMicroseconds(10);
   digitalWrite(triger,LOW);
    
    duration = pulseIn(echo,HIGH); //measure duration of pulse in microsec
    distance =duration * .034/2; 
  return distance; 
  
  }
 
void Park(){
  right();
  analogWrite(en,63);
  delay(1400); 
  Stop();
  delay(2000);
  servoFront.write(180);
  servoFront.write(90);
  delay(1500);
  while(UFun(trigPin,echoPin2)>10){
    analogWrite(en,57); 
    forward();
    }
    Stop();
}
  

void find_slot()
{
   while (true) {
    int frontDistance = UFun(trigPin,echoPin2);
    if(frontDistance > 23)
    {
      int backDistance = UFun(trigPinBack,echoPin1);
      if (backDistance > 23) {
      Stop();
      break;
    }
    }
    forward();
  }
}

