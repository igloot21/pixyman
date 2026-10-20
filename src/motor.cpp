#include <motor.h>

// initierar pins för motorer
int m2d2pwm = 23;
int m2d1pwm = 24;
int in1m1 = 5;
int in2m1 = 4;
int m1d1pwm = 25;
int m1d2pwm = 26;
int in1m2 = 14;
int in2m2 = 13;

void setupMotors()
{
    // Sätter mode på outputpins

    pinMode(in1m1, OUTPUT);
    pinMode(in2m1, OUTPUT);
    pinMode(m1d1pwm, OUTPUT);
    pinMode(m1d2pwm, OUTPUT);

    pinMode(in1m2, OUTPUT);
    pinMode(in2m2, OUTPUT);
    pinMode(m2d2pwm, OUTPUT);
    pinMode(m2d1pwm, OUTPUT);
}

void TurnRobot(String direction) // Funktion för att styra roboten
{
    if (direction == "right")
    {
        // sväng höger
        digitalWrite(m1d1pwm, LOW);
        digitalWrite(m1d2pwm, HIGH);
        digitalWrite(in1m1, HIGH);
        digitalWrite(in2m1, LOW);

        digitalWrite(in1m2, LOW);
        digitalWrite(in2m2, LOW);
    }
    else if (direction == "left")
    {
        // sväng vänster
        digitalWrite(m2d1pwm, LOW);
        digitalWrite(m2d2pwm, HIGH);
        digitalWrite(in2m2, HIGH);
        digitalWrite(in1m2, LOW);

        digitalWrite(in1m1, LOW);
        digitalWrite(in2m1, LOW);
    }
    else if (direction == "forward")
    {
        // åker framåt
        digitalWrite(m1d1pwm, LOW);
        digitalWrite(m1d2pwm, HIGH);
        digitalWrite(in1m1, HIGH);
        digitalWrite(in2m1, LOW);

        digitalWrite(m2d1pwm, LOW);
        digitalWrite(m2d2pwm, HIGH);
        digitalWrite(in1m2, LOW);
        digitalWrite(in2m2, HIGH);
    }
    else if (direction == "backward")
    {
        // åker bakåt
        digitalWrite(m1d1pwm, LOW);
        digitalWrite(m1d2pwm, HIGH);
        digitalWrite(in1m1, LOW);
        digitalWrite(in2m1, HIGH);

        digitalWrite(m2d1pwm, LOW);
        digitalWrite(m2d2pwm, HIGH);
        digitalWrite(in2m2, LOW);
        digitalWrite(in1m2, HIGH);
    }
    else if (direction == "stop")
    { // Stop
        digitalWrite(in1m1, LOW);
        digitalWrite(in2m1, LOW);
        digitalWrite(in1m2, LOW);
        digitalWrite(in2m2, LOW);
    }
    else
    { // stannar roboten om ingen giltig riktning anges
        digitalWrite(in1m1, LOW);
        digitalWrite(in2m1, LOW);
        digitalWrite(in1m2, LOW);
        digitalWrite(in2m2, LOW);
    }
}
