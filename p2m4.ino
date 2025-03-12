// Ocean Environment (High Wind)
const int AIN1 = 13;         
const int AIN2 = 12;         
const int PWMA = 11;  
const int button1 = 4; 
const int button2 = 3;  
const int button3 = 2;  
const int powerButton = 5;
const int bestLED = 9;
const int mediumLED = 8;
const int worstLED = 7;
int motorspeed = 0;
int currentled = 0;
bool powerState = false;

void setup() {
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(powerButton, INPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(bestLED, OUTPUT);
    pinMode(mediumLED, OUTPUT);
    pinMode(worstLED, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    
    //on off switch
    if (digitalRead(powerButton) == HIGH) {
        delay(500);
        powerState = !powerState;
      	Serial.print(powerState);
      	motorspeed = 0;
      	currentled = 0;	
    }
  	
    //if the power button is on
  	if (powerState == 1) {
        //if the best button pushed
        if (digitalRead(button1) == HIGH) {
          	Serial.print("2");// Best turbine'
            motorspeed = 255;
			      currentled = bestLED; 
            //turns on led and motor
        }
        
        //if the medium button pushed
      	if (digitalRead(button2) == HIGH) {
          	Serial.print("3");
          	motorspeed = 180;
			      currentled = mediumLED;
            //turns on led and motor 
        }
        //if the worst button pushed
      	if (digitalRead(button3) == HIGH) {
          	Serial.print("4");
          	motorspeed = 100;
			      currentled = worstLED; 
            //turns on led and motor
        }
    }
  	//turn on motor and led
    setTurbine(motorspeed, currentled);
    spinMotor(motorspeed);
}


//makes led work
void setTurbine(int speed, int activeLED) {

    digitalWrite(mediumLED, activeLED == mediumLED ? HIGH : LOW);
    digitalWrite(bestLED, activeLED == bestLED ? HIGH : LOW);
    digitalWrite(worstLED, activeLED == worstLED ? HIGH : LOW);
}

//make motor work
void spinMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

