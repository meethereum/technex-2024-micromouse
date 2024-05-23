#include "floodfillfunc.h"
#include "Deque.h"
#include <StackArray.h>
#include <Pair.h>
#include <Vector.h>

// Motors
const byte MOTOR_A = 3;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

const float stepcount = 20.00;  // 20 Slots in disk, change if different
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

volatile int counter_A = 0;
volatile int counter_B = 0;

int enA = 10;
int in1 = 9;
int in2 = 8;

int enB = 5;
int in3 = 7;
int in4 = 6;

void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 

void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}

int CMtoSteps(float cm) {
  int result;
  float circumference = (wheeldiameter * 3.14) / 10;
  float cm_step = circumference / stepcount;
  float f_result = cm / cm_step;
  result = (int) f_result;
  return result;
}

void moveForward(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
 
   // Set Motor B forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
   }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 
 
}

void turnRight(int steps, int mspeed) {
   counter_A = 0;
   counter_B = 0;
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   while (steps > counter_A && steps > counter_B) {
    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
   }
   analogWrite(enA, 0);
   analogWrite(enB, 0);
   counter_A = 0;
   counter_B = 0;
}

void turnLeft(int steps, int mspeed) {
   counter_A = 0;
   counter_B = 0;
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
   while (steps > counter_A && steps > counter_B) {
    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
   }
   analogWrite(enA, 0);
   analogWrite(enB, 0);
   counter_A = 0;
   counter_B = 0;
}

int leftWall=11;
int rightWall=13;
int lfwall=12;
int rfwall=2;

bool wallLeft=false;
bool wallFront=false;
bool wallRight=false;

int checkWalls(int leftWall,int rightWall,int lfWall,int rfWall){
  delay(1000);
  wallLeft=false;
   wallFront=false;
   wallRight=false;
  if(digitalRead(leftWall)==1){
      wallLeft=true;
      Serial.println("wall at left");
  }
  if(digitalRead(rightWall)==0){
      wallRight=true;
      Serial.println("wall at right");
  }
   if(digitalRead(lfWall)==0 ){
      wallFront=true;
      Serial.println("Wall at front");
  }
  
  return 0;
}

void setup(){
  Serial.begin(9600);
  pinMode(leftWall,INPUT);
  pinMode(rightWall,INPUT);
  pinMode(lfwall,INPUT);
  pinMode(rfwall,INPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_A), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt(MOTOR_B), ISR_countB, RISING);
  delay(3000);
}

void loop(){
  //delay(100);
  checkWalls(leftWall,rightWall,lfwall,rfwall);
  if (wallLeft) {
    turnLeft(9,80);
    Serial.println("turning left");
  }
  while (wallFront) {
    checkWalls(leftWall,rightWall,lfwall,rfwall);
    turnRight(9,80);Serial.println("turning right");
    delay(100);
    //  Serial.println("wall at front");
  }
  delay(80);
  moveForward(15,80);
  Serial.println("moving forward");
}
  
