#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7
#define trigPin4 8
#define echoPin4 9
#define ledSensor1 10
#define ledSensor2 11
#define ledSensor3 12
#define ledSensor4 13

long duration, distance, paperSensor, metalSensor, plasticSensor, glassSensor;

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(ledSensor1, INPUT);
  pinMode(ledSensor2, INPUT);
  pinMode(ledSensor3, INPUT);
  pinMode(ledSensor4, INPUT);

}

void loop() {
  SonarSensor(trigPin1, echoPin1);
  metalSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  plasticSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  glassSensor = distance;
  SonarSensor(trigPin4, echoPin4);
  paperSensor = distance;

  Serial.print(metalSensor);
  Serial.print(" - ");
  Serial.print(plasticSensor);
  Serial.print(" - ");
  Serial.print(glassSensor);
  Serial.print(" - ");
  Serial.print(paperSensor);

  if (metalSensor <= 18){
    digitalWrite(ledSensor1, HIGH);
  }

  else{
    digitalWrite(ledSensor1, LOW);
  }

  if (plasticSensor <= 18){
    digitalWrite(ledSensor2, HIGH);
  }

  else{
    digitalWrite(ledSensor2, LOW);
  }
  
  if (glassSensor <= 18){
    digitalWrite(ledSensor3, HIGH);
  }

  else{
    digitalWrite(ledSensor3, LOW);
  }
  
  if (paperSensor <= 18){
    digitalWrite(ledSensor4, HIGH);
  }

  else{
    digitalWrite(ledSensor4, LOW);
  }
}

void SonarSensor(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}
