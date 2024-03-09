#define NUM_SENSORS 4  // Number of sensors

const int trigPins[NUM_SENSORS] = {2, 4, 6, 8};  // Array of trigger pins
const int echoPins[NUM_SENSORS] = {3, 5, 7, 9};  // Array of echo pins
const int ledPins[NUM_SENSORS] = {10, 11, 12, 13};  // Array of LED pins

int distances[NUM_SENSORS];  // Array to store sensor readings

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    distances[i] = readSonarSensor(trigPins[i], echoPins[i]);
    digitalWrite(ledPins[i], distances[i] <= 18 ? HIGH : LOW);  // LED control within readSonarSensor
  }

  Serial.print(distances[0]);
  Serial.print(" - ");
  Serial.print(distances[1]);
  Serial.print(" - ");
  Serial.print(distances[2]);
  Serial.print(" - ");
  Serial.print(distances[3]);
  Serial.println();
}

int readSonarSensor(int sensorTrigPin, int sensorEchoPin) {
  digitalWrite(sensorTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
  long duration = pulseIn(sensorEchoPin, HIGH);
  int distance = (duration / 2) / 29.1;
  return distance;
}
