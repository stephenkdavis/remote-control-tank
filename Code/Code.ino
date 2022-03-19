/**
 * Stephen K. Davis
 * stephendavis.io
 * Remote Control Tank
 */

#include <Servo.h>
#include <IRremote.h>

Servo fronteyes;

/**
 * Traffic light pin codes
 */
int yellowCounter = 0;
int redLED = 2;
int yellowLED = 3;
int greenLED = 4;
int ledGND = 5;

/**
 * Servo Information - "fronteyes"
 * Initial starting point is 140
 * Optimized rotation range is between 100 and 180
 * The servo is connected to the board on pin 5
 */
int servoPin = 10;
int servoHomeLocation = 140;
int servoLocation = 0;

/**
 * Motor Information
 */
int motor1 = 6;
int motor2 = 7;
int motor3 = 8;
int motor4 = 9;

/**
 * IR Sensor Information
 */
int irGNDPin = 11;
int irPWRPin = 12;
int irSIGPin = 13;
//IRrecv irrecv(irSIGPin);
//decode_results results;

/**
 * Method to create the initial system setup
 */
void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(ledGND, OUTPUT);
  
  digitalWrite(ledGND, LOW);
  
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);

  pinMode(motor1, OUTPUT);
  digitalWrite(motor1, LOW);
  pinMode(motor2, OUTPUT);
  digitalWrite(motor2, LOW);
  pinMode(motor3, OUTPUT);
  digitalWrite(motor3, LOW);
  pinMode(motor4, OUTPUT);
  digitalWrite(motor4, LOW);
  
  pinMode(irGNDPin, OUTPUT);
  digitalWrite(irGNDPin, LOW);
  pinMode(irPWRPin, OUTPUT);
  digitalWrite(irPWRPin, HIGH);
  pinMode(irSIGPin, INPUT);
  Serial.begin(9600);
  //irrecv.enableIRIn();
  IrReceiver.begin(irSIGPin, true);
  
  fronteyes.attach(servoPin);
  fronteyes.write(servoHomeLocation);
  
  delay(1000);

  // Ready to go
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}

/**
 * Method for the main function control
 */
void loop() {
  if (IrReceiver.decode()) {
  
    // Print the results.value
    //Serial.println(results.value, DEC);
    unsigned long inputValue = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(inputValue, DEC);
    
    // Check to see if input is the UP button & return that value
    if (inputValue == 2701821934) {
      Serial.println("Button UP has been pressed on the Apple Remote!");
      directionForward();
      
    // Check to see if input is the DOWN button & return that value
    } else if (inputValue == 2701953006) {
      Serial.println("Button DOWN has been pressed on the Apple Remote!");
      directionBackward();
      
    // Check to see if input is the RIGHT button & return that value
    } else if (inputValue == 2701559790) {
      Serial.println("Button RIGHT has been pressed on the Apple Remote!");
      directionRight();
      
    // Check to see if input is the LEFT button & return that value
    } else if (inputValue == 2701756398) {
      Serial.println("Button LEFT has been pressed on the Apple Remote!");
      directionLeft();

    // Check to see if input is the CENTER button & return that value
    } else if (inputValue == 2707195886) {
      Serial.println("Button CENTER has been pressed on the Apple Remote!");
      
      // This if-else statement determines whether the headlight is on or off using a simple counter
      if (yellowCounter % 2 == 0) {
        digitalWrite(yellowLED, HIGH);
        yellowCounter++;
      } else {
        digitalWrite(yellowLED, LOW);
        yellowCounter++;
      }
      
    // Check to see if input is the MENU button & return that value
    } else if (inputValue == 2701363182) {
      Serial.println("Button MENU has been pressed on the Apple Remote!");
      policeLights();
      
    // Check to see if input is the PLAY/PAUSE button & return that value
    } else if (inputValue == 2707392494) {
      Serial.println("Button PLAY/PAUSE has been pressed on the Apple Remote!");
      frontEyesServo();
    }

    // Ready IR to receive the next input
    IrReceiver.resume();
  }
}

/**
 * Method to control the Front Servo called frontEyes
 */
void frontEyesServo() {
  for (int i = 1; i <= 3; i++) {
   fronteyes.write(100);
   delay(750);
   fronteyes.write(180);
   delay(750); 
  }
  fronteyes.write(servoHomeLocation);
}

/**
 * Method to control the traffic lights in police cruiser lightbar style
 */
void policeLights() {
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);

  for (int i = 1; i <= 2; i++) {
    for (int i = 1; i <= 3; i++) {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(300);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      delay(300);
    }
  
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    
    for (int i = 1; i <= 5; i++) {
      digitalWrite(redLED, HIGH);
      delay(50);
      digitalWrite(redLED, LOW);
      delay(50);
    }
  
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    
    for (int i = 1; i <= 5; i++) {
      digitalWrite(greenLED, HIGH);
      delay(50);
      digitalWrite(greenLED, LOW);
      delay(50);
    }
  
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
  }
}

/**
 * Method to control forward direction motor control
 * Delay is to determine how long the tank moves forward for in time value
 */
void directionForward() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  delay(1000);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

/**
 * Method to control backwards direction motor control
 * Delay is to determine how long the tank moves backwards for in time value
 */
void directionBackward() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(1000);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

/**
 * Method to control turning right
 * Delay is to determine how long the tank turns right for in time value
 */
void directionRight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  delay(250);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

/**
 * Method to control turning left
 * Delay is to determine how long the tank turns left for in time value
 */
void directionLeft() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  delay(250);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}
