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
const int LSL = A3;
const int LSC = A4;
const int LSR = A5;

int switchPin = 7;
int maxSpeed = 250;
int defaultSpeed = 175;
int rightSpeed = 215;
int leftSpeed = 150;
int turnSpeed = 150;
int lineThreshold = 750;

// Sensor inputs init
int IRFin = 0;
int IRRin = 0;
int IRLin = 0;
int LSCin = 0;
int LSRin = 0;
int LSLin = 0;

void setup() {

    Serial.begin(9600);
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
        //line_follow();
        //forward(defaultSpeed);
        //testDance(defaultSpeed);
        wall_follow();
    } else {
        stop();
    }
    //wall_follow()
}

void line_follow() {
    // Taking inputs
    LSCin = analogRead(LSC);
    LSRin = analogRead(LSR);
    LSLin = analogRead(LSL);

    // Line sensor turn logic
//        Serial.println(LSCin);
//        Serial.println(LSRin);
//        Serial.println(LSLin);
//        delay(1000);
    forward(leftSpeed, rightSpeed);
    delay(50);
    if(LSCin > lineThreshold && LSRin < lineThreshold && LSLin < lineThreshold) {   // Only middle sensor senses
        forward(leftSpeed, rightSpeed);
    }
    else if(LSRin > lineThreshold && LSLin < lineThreshold) {  // Right senses
        turn('r', turnSpeed);
    }
    else if(LSRin < lineThreshold && LSLin > lineThreshold) {  // Left senses
        turn('l', turnSpeed);
    }
    else if(LSCin > lineThreshold && LSRin > lineThreshold && LSLin > lineThreshold) {  // All sense
        stop();
    }
    else if(LSCin > lineThreshold && LSRin > lineThreshold && LSLin < lineThreshold) {  // Sense right sharp turn
        turn('r', maxSpeed);
    }
    else if(LSCin > lineThreshold && LSRin < lineThreshold && LSLin > lineThreshold) {  // Sense left sharp turn
        turn('l', maxSpeed);
    } else {
        forward(leftSpeed, rightSpeed);
    }
    delay(50);
}

void wall_follow() {
    // Taking inputs
    IRFin = analogRead(IRF);
    IRRin = analogRead(IRR);
    IRLin = analogRead(IRL);
    Serial.println(IRFin);

    // IR Sensor turn logic
    forward(leftSpeed, rightSpeed);
    if(IRRin - IRLin > 20) {
        turn('l', turnSpeed);
    }
    else if(IRRin - IRLin < -20) {
        turn('r', turnSpeed);
    }
    else if(IRF > 300) {
        reverse(leftSpeed, rightSpeed);
    } else {
        forward(leftSpeed, rightSpeed);
    }
    delay(100);
}    

void forward(int leftMotorSpeed, int rightMotorSpeed) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, abs(leftMotorSpeed));
    analogWrite(PWMB, abs(rightMotorSpeed));
}

void reverse(int leftMotorSpeed, int rightMotorSpeed) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    analogWrite(PWMA, abs(leftMotorSpeed));
    analogWrite(PWMB, abs(rightMotorSpeed));
}

void stop() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, abs(0));
    analogWrite(PWMB, abs(0));
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

void testDance(int motorSpeed) {
    //forward(motorSpeed);
    delay(500);
    stop();
    delay(500);
    reverse(leftSpeed, rightSpeed);
    delay(500);
    turn('r', motorSpeed);
    delay(500);
    turn('l', motorSpeed);
    delay(500);
}
