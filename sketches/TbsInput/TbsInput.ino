/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <Arduino.h>
Servo elevationOutputServo;  // create servo object to control a servo
Servo elevationInputServo;
/*
 * Pin definitions
 */

 #define PIN_SERVO_ELEVATION 9
 #define PIN_RADIO_ELEVATION 2
 /*
  * END PIN DEFS
  */

 /*
  * SERVO SPEED DEFINITIONS
  */
  #define servoSpeedSlowest 2
  #define servoSpeedSlower 4
  #define servoSpeedMedium 6
  #define servoSpeedFaster 8
  #define servoSpeedFastest 10

/*
  * SERVO LIMITS
  */  
#define SERVO_MIN 0
#define SERVO_MAX 179

int currentElevationRading = 0;    // variable to read the value from the analog pin
int lastElevationReading = 0;

unsigned long now;                        // timing variables to update data at a regular interval                  
unsigned long rc_update;
const int channels = 1;                   // specify the number of receiver channels
float RC_in[channels];                    // an array to store the calibrated input from receiver 



void setupPins()
{
  Serial.println("Attaching pins");
  pinMode(PIN_RADIO_ELEVATION, INPUT);
  pinMode(PIN_SERVO_ELEVATION, OUTPUT);
  elevationOutputServo.attach(PIN_SERVO_ELEVATION);  // attaches the servo on pin 9 to the servo object
  elevationInputServo.attach(PIN_RADIO_ELEVATION);
  Serial.println("Attached pins");
  Serial.println(elevationInputServo.read());
  Serial.println(elevationOutputServo.read());
}

void printRadioSignal(){
  currentElevationRading = elevationInputServo.read();
  if (currentElevationRading != lastElevationReading) {
    Serial.println(currentElevationRading);
    lastElevationReading = currentElevationRading;
  }
}

void printRadioSignalAnalog(){
  currentElevationRading = elevationInputServo.read();
  if (currentElevationRading != lastElevationReading) {
    Serial.println(currentElevationRading);
    lastElevationReading = currentElevationRading;
  }
}

void setup() {
  //setupPins();    
  setup_pwmRead();                      
  Serial.begin(9600);
}

void loop() {  
    
    now = millis();
    
    if(RC_avail() || now - rc_update > 25){   // if RC data is available or 25ms has passed since last update (adjust to be equal or greater than the frame rate of receiver)
      
      rc_update = now;                           
      
      print_RCpwm();                        // uncommment to print raw data from receiver to serial
      
      for (int i = 0; i<channels; i++){       // run through each RC channel
        int CH = i+1;
        
        RC_in[i] = RC_decode(CH);             // decode receiver channel and apply failsafe
        
        //print_decimal2percentage(RC_in[i]);   // uncomment to print calibrated receiver input (+-100%) to serial       
      }
      //Serial.println();                       // uncomment when printing calibrated receiver input to serial.
    }
}

