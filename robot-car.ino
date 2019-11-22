//Pin Configurations

const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;
const int BIN1 = 10;
const int BIN2 = 9;
const int PWMB = 8; 
int switchPin = 7;

void setup() {
    pinMode(switchPin, INPUT_PULLUP);

    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
}

void loop() {

    if(digitalRead(switchPin) == LOW) {      // switchPin is on (outputting LOW)
        spinMotor(250);
    } else {
        spinMotor(0);
    }
}

void spinMotor(int motorSpeed) {
    if (motorSpeed > 0) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);   
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }
    else if (motorSpeed < 0) {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }
    else {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }
    analogWrite(PWMA, abs(motorSpeed));
    analogWrite(PWMB, abs(motorSpeed));
}
