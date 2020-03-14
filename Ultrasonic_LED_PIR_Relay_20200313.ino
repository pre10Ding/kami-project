//Cheng Shao 2020
//Ultrasonic code that works pretty well without any external libraries
//Combined with PIR sensor for some testing, using non-blocking structure

#define trigPin 11
#define echoPin 12
#define led 7
#define led2 6
#define led3 5

#define ledPin 13
#define pirPin 2
#define relayPin 4

unsigned long previousMillis = 0;
const long interval = 500;
unsigned long previousMillisPIR = 0;
const long intervalPIR = 5000;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {

//setting up the non-blocking code and making it slightly more robust
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

 //This is Ultrasonic sensor stuff, not sure how it works
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;


  //currently setup to turn on 1 out of 3 LED based on distance
  
  //less than 10cm turn on this one and turn off the other 2
  if (distance < 10) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    digitalWrite(led3, LOW);
  }

  //less than 200, but more than 50, turn on the 2nd LED
  else if (distance >50) {
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3, HIGH);
  }

  //more than 200/out of bounds, turn on the 3rd one
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3, LOW);

  }

  //setting a out of bounds range
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  }

  //PIR stuff same as PIR_and_RelayLights_20200313
  int sensorValue = digitalRead(pirPin);
    if(sensorValue==1) {
      digitalWrite(ledPin,HIGH);
      digitalWrite(relayPin,HIGH);
      previousMillisPIR = currentMillis;

    }
    else if(currentMillis - previousMillisPIR >= intervalPIR) {
      
      digitalWrite(ledPin,LOW);
      digitalWrite(relayPin,LOW);
    }
  //}
  
}
