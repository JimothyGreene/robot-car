// Pin Configurations
// Right motor = A; Left motor = B
const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;
const int BIN1 = 10;
const int BIN2 = 9;
const int PWMB = 8; 

/* IR Sensors
 * Higher number = closer to obstacle (20cm = 272, 40cm = 145, 60cm = 116, 80cm = 104) roughly
 * 10-80 cm effective measuring distance
 */
const int IRF = A1;
const int IRR = A0;
const int IRL = A2;

/* Line Sensors
 * 
 */
const int LSR = A3;
const int LSC = A4;
const int LSL = A5;

int switchPin = 7;
int motorSpeed = 250;

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

    if(digitalRead(switchPin) == LOW) {

    } else {
        stop();
    }
}

void forward(int motorSpeed) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, abs(motorSpeed));
    analogWrite(PWMB, abs(motorSpeed));
}

void reverse(int motorSpeed) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    analogWrite(PWMA, abs(motorSpeed));
    analogWrite(PWMB, abs(motorSpeed));
}

void stop() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, abs(motorSpeed));
    analogWrite(PWMB, abs(motorSpeed));
}

void turn(char direction, int motorSpeed) {
    if(direction == 'r') {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }
    else if(direction == 'l') {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }

    analogWrite(PWMA, abs(motorSpeed));
    analogWrite(PWMB, abs(motorSpeed));
}

void testDance() {
    forward(motorSpeed);
    delay(500);
    stop();
    delay(500);
    reverse(motorSpeed);
    delay(500);
    turn('r', motorSpeed);
    delay(500);
    turn('l', motorSpeed);
    delay(500);
}
