#define trigPin1 12
#define echoPin1 11
#define trigPin2 6
#define echoPin2 7

int counter = 0;
int currentState1 = 0;
int previousState1 = 0;
int currentState2 = 0;
int previousState2 = 0;

// Define traffic light control pins
const int greenLightPin = 2;
const int yellowLightPin = 3;
const int redLightPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialize traffic light control pins
  pinMode(greenLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);
}

void loop() {
  long duration1, distance1, duration2, distance2;
  
  // First ultrasonic sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  // Second ultrasonic sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;

  // Detect cars passing through first sensor
  if (distance1 <= 20) {
    currentState1 = 1;
  } else {
    currentState1 = 0;
  }

  // Detect cars passing through second sensor
  if (distance2 <= 20) {
    currentState2 = 1;
  } else {
    currentState2 = 0;
  }

  // Decrease car count if a car passes through the second sensor
  if (currentState2 != previousState2 && currentState2 == 1) {
    if (counter - 1 < 0){
      Serial.println("Car cant be below 0");
    }
    else{
      counter--;
      Serial.println("Number of Cars passed through Lane 2   " + String(counter));
      adjustTrafficLights(counter);
    }

  }

  // Increase car count if a car passes through the first sensor
  if (currentState1 != previousState1 && currentState1 == 1) {
    counter++;
    Serial.println("Number of Cars passed through Lane 1: " + String(counter));
    adjustTrafficLights(counter);
  }

  previousState1 = currentState1;
  previousState2 = currentState2;
}

void adjustTrafficLights(int vehicleCount) {
  // Adjust traffic lights based on the number of vehicles detected
  if (vehicleCount <= 5) {
    // Light up green for this direction
    digitalWrite(greenLightPin, HIGH);
    digitalWrite(yellowLightPin, LOW);
    digitalWrite(redLightPin, LOW);
  } else if (vehicleCount <= 10) {
    // Light up yellow for this direction
    digitalWrite(greenLightPin, LOW);
    digitalWrite(yellowLightPin, HIGH);
    digitalWrite(redLightPin, LOW);
  } else {
    // Light up red for this direction
    digitalWrite(greenLightPin, LOW);
    digitalWrite(yellowLightPin, LOW);
    digitalWrite(redLightPin, HIGH);
  }
}
