#include <AccelStepper.h>
#include <Servo.h>
// 64 step motor

// paste csv file below adding commas to the end of the rows
double Array[]= {
1,7.2,90,1,400,
2,14.4,90,1,400,
3,7.2,90,1,400,
4,14.4,90,1,400,
5,7.2,6.283185307,0,0,};

Servo myservo;
int pos = 0;

long stepcount = 0;
long counter = 0;
long checker = 0;

AccelStepper stepperL(AccelStepper::FULL4WIRE, 50, 52, 51, 53);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 46, 48, 47, 49);
AccelStepper stepperE1(AccelStepper::FULL4WIRE, 42, 44, 43, 45);
AccelStepper stepperE2(AccelStepper::FULL4WIRE, 38, 40, 39, 41);

//set speed at which the buggy will move forwards/backwards
long x = 50;

//set speed at which the buggy will turn clockwise/counterclockwise
long xt = 150;

//set extruder speed
long y = 400;

void setup() {
myservo.attach(37);

//settings for left and right motor
stepperL.setCurrentPosition(0);
stepperL.setMaxSpeed(20000);
stepperL.setSpeed(x);

stepperR.setCurrentPosition(0);
stepperR.setMaxSpeed(20000);
stepperR.setSpeed(-x);

// settings for extruder1 , try positive if not extruding
stepperE1.setCurrentPosition(0);
stepperE1.setMaxSpeed(20000);
stepperE1.setSpeed(-y);

// settings for extruder2 , try positive if not extruding
stepperE2.setCurrentPosition(0);
stepperE2.setMaxSpeed(20000);
stepperE2.setSpeed(-y);
}

//FUNCTIONS

//function to reset motors to position 0 - add any new motors (servomotor)
void motorreset()
{
stepperL.setCurrentPosition(0);
stepperR.setCurrentPosition(0);
stepperE1.setCurrentPosition(0);
stepperE2.setCurrentPosition(0);
}

//function to move the buggy forwards
void moveforward(long position)
{
stepperL.moveTo(position);
stepperL.setSpeed(x);
stepperR.moveTo(-position);
stepperR.setSpeed(-x);
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
}
}

//function to move the buggy backwards
void movebackward(long position)
{
stepperL.moveTo(-position);
stepperL.setSpeed(x);
stepperR.moveTo(-position);
stepperR.setSpeed(x);
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
}
}

//function to turn the buggy clockwise
void turnclockwise(long position)
{
stepperL.moveTo(position);
stepperL.setSpeed(xt);
stepperR.moveTo(position);
stepperR.setSpeed(xt);
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
}
}

//function to turn the buggy counterclockwise
void turncounterclockwise(long position)
{
stepperL.moveTo(-position);
stepperL.setSpeed(-xt);
stepperR.moveTo(-position);
stepperR.setSpeed(-xt);
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
}
}

//function to switch to material 1 change to positive if needed
void switch1(long position)
{
myservo.write(position);
delay (1000);
}

//function to switch to material 2
void switch2(long position)
{
myservo.write(position);
delay (1000);
}

//function to extrude material 1 and move forward
void moveforwardextrude1(long position,long speed)
{
stepperL.moveTo(position);
stepperL.setSpeed(x);
stepperR.moveTo(-position);
stepperR.setSpeed(-x);
//extruder rate = buggy movement rate * constant
stepperE1.moveTo(-20000);
stepperE1.setSpeed(-speed);
// while loop means the extruder and fan only runs when the buggy is moving
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
stepperE1.runSpeedToPosition();
}
}

//function to extrude material 2 and move forward
// FAN NEEDS TO BE ADDED (only to this function and E2 as only required when printing occurs?)
void moveforwardextrude2(long position, long speed)
{
stepperL.moveTo(position);
stepperL.setSpeed(x);
stepperR.moveTo(-position);
stepperR.setSpeed(-x);
// try positive position and speed if not working, number is a constant where extruder rate = buggy movement rate * number
stepperE2.moveTo(-20000);
stepperE2.setSpeed(-speed);
// while loop means the extruder only runs when the buggy is moving
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
stepperE2.runSpeedToPosition();
}
}

void loop() {
delay(2000);

counter = 1;
checker = 1;

while (counter = checker) {
motorreset();
if (Array[1+((counter-1)*5)] < 0) {
turnclockwise((Array[1+((counter-1)*5)])/0.0982);
}
else {
turncounterclockwise((Array[1+((counter-1)*5)])/0.0982);
}
motorreset();
//if not printing material
if (Array[3+((counter-1)*5)] == 0) {
moveforward((Array[2+((counter-1)*5)])/0.14);
}
// if printing material 1
else if (Array[3+((counter-1)*5)] == 1) {
switch1(85);
moveforwardextrude1(((Array[2+((counter-1)*5)])/0.14),(Array[4+((counter-1)*5)]));
}
// if printing material 2
else if (Array[3+((counter-1)*5)] == 2) {
switch2(105);
moveforwardextrude2(((Array[2+((counter-1)*5)])/0.14),(Array[4+((counter-1)*5)]));
}
counter = counter + 1;
checker = Array[(counter-1)*5];
}
exit(0);
}
