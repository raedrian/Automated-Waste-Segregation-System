#include <Servo.h>
#include <AccelStepper.h>
#define Servo_PWM 6 // A descriptive name for D6 pin of Arduino to provide PWM signal
#define stepPin 2
#define dirPin 3
Servo Gate;  // Define an instance of of Servo with the name of "Gate"
  
const int trigPin = 8;
const int echoPin = 9;
// defines variables
long duration;
int distance;

int sensorMetal = 4;
int sensorGlass = 3;
int sensorPlastic = 2;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 10) {

    // int metalValue = digitalRead(sensorMetal);
    // delay(500);
    // Serial.print("Inductive Sensor Value: ");
    // Serial.println(metalValue);
    
    // // Check conductive sensor
    // int plasticValue = digitalRead(sensorPlastic);
    // delay(500);
    // Serial.print("Plastic Conductive Sensor Value: ");
    // Serial.println(plasticValue);

    // int glassValue = digitalRead(sensorGlass);
    // delay(500);
    // Serial.print("Glass Conductive Sensor Value: ");
    // Serial.println(glassValue);
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(400);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(400); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 1600; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(400);
  }
  delay(1000);
      Gate.attach(Servo_PWM);
      Gate.write(180); //Turn clockwise at high speed
      delay(500);
      Gate.detach();//Stop. You can use deatch function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
      delay(2000);
      Gate.attach(Servo_PWM);//Always use attach function after detach to re-connect your servo with the board
      Gate.write(0);
      delay(500);
      Gate.detach();//Stop
      delay(1000);

  }
  delay(100);
}