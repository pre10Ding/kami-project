//Cheng Shao 2020
//This code is for the PIR motion sensors (the bulb looking one)
//The sensor is controlling a relay to flash some lights on and off
//Lights flash in 3 different patterns (modes) that are hardcoded
//This code utilizes a non-blocking structure with the millis() func


const int ledPin=13;//The led to indicate the motion
const int relayPin=4;//The led to indicate the motion
const int pirPin=2;//The led to indicate the motion


unsigned long prevTime = 0;
unsigned long currTime = 0;
int period = 0;
int ledState = 1;

//MANUALLY set how the LED will flash here
int mode = 1;
//mode 1 is just ON
//mode 2 is FLICKER RANDOMLY
//mode 3 is FLICKER EVENLY

int flickerFrequency = 200;


void setup(){
  
  Serial.begin(9600);

  //This pin is for the PIR sensor, which will keep outputting "1" 
  //once it detects motion until the preset time (set by the potentiometer
  //knob on the actual sensor's board) has been reached.
  pinMode(pirPin, INPUT);//Use pin 2 to receive the signal outputted by the module 
  
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  prevTime = millis();
  period = 400;

}


void loop() {

  //set the current time
  currTime = millis();
  int sensorValue = digitalRead(pirPin);

  if (mode == 1) {

    //the PIR sensor will simply output 0 or 1
    if(sensorValue==1)
      ledState = 1;
    else {
      ledState = 0;
     }
  }
  
  if (mode == 2) {
    if(sensorValue == 1) {
      flicker(50, 600);
    } else {
      ledState = 0;
    }
  }

  if(mode == 3) {
    if(sensorValue == 1) {
      flicker(flickerFrequency, flickerFrequency);
    } else {
      ledState = 0;
    }
  }
  
  Serial.println(sensorValue, DEC);//Print the state of the signal through the serial monitor.
  digitalWrite(ledPin,ledState);
  digitalWrite(relayPin, ledState);
}

//randomly turns led on and off
void flicker(int min, int max) {
  //compares the previously set time against the current time to see
  //if a certain time (period) has elapsed.
  if(currTime > prevTime+period) {
    //if true, then record the current time
    prevTime = millis();
    period = random (min, max);
    ledState = (ledState-1)*-1;
  }
}
