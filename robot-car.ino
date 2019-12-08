// Pin Configurations
// Right motor = A; Left motor = B
const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;
const int BIN1 = 10;
const int BIN2 = 9;
const int PWMB = 8;

/* IR Sensors
 * Higher number = closer to obstacle
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
int maxSpeed = 255;
int lowSpeed = 150;
int defaultSpeed = 150;
int turnSpeed = 140;
int lineThreshold = 600;
int frontThreshold = 600;
int nextCount = 0;
int accelCount = 0;

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
        if(nextCount > 20) {
            wall_follow();
        } else {
            line_follow();
        }
        Serial.println(nextCount);
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
    IRFin = analogRead(IRF);

    // Line sensor turn logic (black is high)
    forward(defaultSpeed);
    if(LSCin > lineThreshold && LSRin < lineThreshold && LSLin < lineThreshold) {   // Only middle sensor senses
        forward(defaultSpeed);
    }
    else if(LSCin < lineThreshold && LSRin < lineThreshold && LSLin < lineThreshold) {
        nextCount++;
    }
    else if(IRFin > frontThreshold) {
        uturn();
    }
    else if(LSC < lineThreshold && LSRin < lineThreshold && LSLin > lineThreshold) {  // left senses
        turn('l', turnSpeed);
    }
    else if(LSC < lineThreshold && LSRin > lineThreshold && LSLin < lineThreshold) {  // right senses
        turn('r', turnSpeed);
    }
    else if(LSCin > lineThreshold && LSRin > lineThreshold && LSLin > lineThreshold) {  // All sense
        turn('r', turnSpeed);
        delay(50);
    }
    else if(LSCin > lineThreshold && LSRin < lineThreshold && LSLin > lineThreshold) {  // Sense left sharp turn
        turn('l', maxSpeed);
        delay(50);
    }
    else if(LSCin > lineThreshold && LSRin > lineThreshold && LSLin < lineThreshold) {  // Sense right sharp turn
        turn('r', maxSpeed);
        delay(50);
    } else {
        forward(defaultSpeed);
    }
    delay(50);
}

void wall_follow() {
    // Taking inputs
    IRFin = analogRead(IRF);
    IRRin = analogRead(IRR);
    IRLin = analogRead(IRL);

    // IR Sensor turn logic
    forward(defaultSpeed);
    if(IRRin - IRLin > 30) {
        turn('l', turnSpeed);
        delay(25);
    }
    else if(IRRin - IRLin < -30) {
        turn('r', turnSpeed);
        delay(25);
    } else {
        forward(defaultSpeed);
        delay(25);
    }
    delay(25);
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

void uturn() {
    turn('r', 230);
    delay(300);
    LSCin = analogRead(LSC);
    while(LSCin < lineThreshold) {
        LSCin = analogRead(LSC);
    }
}

void testDance(int motorSpeed) {
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
