#include <Servo.h>

//L293D
//Motor A
const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293
//Motor B
const int motorPin3  = 10; // Pin  7 of L293
const int motorPin4  = 9;  // Pin  2 of L293

// Ultrasonic Sensor
const int triggerPin = 8;
const int echoPin = 7; 

// Servomotor
Servo ultrasonicServo;
int position = 0; // Is it not self-explanatory?

// I2C Module LCD (Test only)

//This will run only one time.
void setup(){

    // Serial Comunication
    Serial.begin(9600);
    
    // Ultrasonic config
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);

    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    
    // Servomotor config
    ultrasonicServo.attach(3);
}

void loop() {

    long estimatedDistance = 0;

    // Servomotor movement
    for(position = 0; position <= 180; position += 1) {
        ultrasonicServo.write(position);
        delay(15);
        // Serial print input
        estimatedDistance = getDistance();
        Serial.print("Serv-Pos: ");
        Serial.print(position);
  	    Serial.print("Distance: ");
  	    Serial.println(estimatedDistance); 
    }
    for(position = 180; position >= 0; position -= 1) {
        ultrasonicServo.write(position);
        delay(15);
        // Serial print input
        estimatedDistance = getDistance();
        Serial.print("Serv-Pos: ");
        Serial.print(position);
  	    Serial.print("Distance: ");
  	    Serial.println(estimatedDistance); 
    }
    // Car Actions
    if (estimatedDistance > 7) {
        goForward();
    } else if (estimatedDistance <= 7) {
        stopMovement();
      	delay(300);
        goBackwards();
      	delay(1000);
        changeLeft();
    }
}



// Ultrasonic function
long getDistance() {

    // Variables
    long t; // Time
    long d; // Distance

    // Sends a tiny little pulse
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // I don't have any clue 'bout this equation.
    t = pulseIn(echoPin, HIGH);
    d = t/59;

    return d;
}

// Motors commands
void goForward() {
    // Both motors will go clockwise
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
}

void goBackwards() {
    // Both motors will go counter-clockwise
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void changeLeft() {
    //Motor A will go counter-clockwise
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}

void changeRight() {
    // Motor B will go counter-clockwise
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void stopMovement() {
    // Motors A and B will stop moving
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}

