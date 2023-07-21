#include <AccelStepper.h>
#include <MultiStepper.h>



// 64 step motor



int Array[]= {
1,45,7.071067812,
2,-45,35,
3,90,35,
4,90,35,
5,90,35,
0,0,0,
0,0,0,
};





long stepcount = 0;
long counter = 0;
long checker = 0;




AccelStepper stepperL(AccelStepper::FULL4WIRE, 50, 52, 51, 53);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 46, 48, 47, 49);
AccelStepper stepperE(AccelStepper::FULL4WIRE, 42, 44, 43, 45);



MultiStepper steppers;



//set speed at which the buggy will move forwards/backwards
long x = 50;



//set speed at which the buggy will turn clockwise/counterclockwise
long xt = 100;



//set extruder speed
long y = 400;



void setup() {



//settings for left and right motor
stepperL.setCurrentPosition(0);
stepperL.setMaxSpeed(20000);
stepperL.setSpeed(x);



stepperR.setCurrentPosition(0);
stepperR.setMaxSpeed(20000);
stepperR.setSpeed(-x);




// settings for extruder, try positive if not extruding
stepperE.setCurrentPosition(0);
stepperE.setMaxSpeed(20000);
stepperE.setSpeed(-y);



steppers.addStepper(stepperL);
steppers.addStepper(stepperR);
}



//FUNCTIONS



//function to reset motors to position 0 - add any new motors (servomotor)
void motorreset()
{
stepperL.setCurrentPosition(0);
stepperR.setCurrentPosition(0);
stepperE.setCurrentPosition(0);
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



//function to switch material
void switchmaterial(long position)
{



// add servo motor




}



//EASIER WITH ONE VARIABLE? SINCE 2ND VARIABLE INPUT IS ALWAYS DEPENDENT ON THE FIRST - AMOUNT EXTRUDED WILL ALWAYS
//BE DEPENDENT ON THE LENGTH OF THE LINE PRINTED IE DISTANCE BUGGY HAS MOVED
//function to extrude and move forward, 2 variables.
void moveforwardextrude(long position)
{
stepperL.moveTo(position);
stepperL.setSpeed(x);
stepperR.moveTo(-position);
stepperR.setSpeed(-x);
// try positive position and speed if not working, number is a constant where extruder rate = buggy movement rate * number
stepperE.moveTo(20000);
stepperE.setSpeed(-y);
// while loop means the extruder only runs when the buggy is moving
while ((stepperL.distanceToGo() != 0) && (stepperR.distanceToGo() != 0))
{
stepperL.runSpeedToPosition();
stepperR.runSpeedToPosition();
stepperE.runSpeedToPosition();
}
}




void loop() {
delay(5000);
counter = 1;
checker = 1;
while (counter = checker) {
// change 3 to the number of columns in excel sheet
checker = Array[(counter-1)*3];
motorreset();
if (Array[1+((counter-1)*3)] < 0) {
turnclockwise((Array[1+((counter-1)*3)])/0.0982);
}
else {
turncounterclockwise((Array[1+((counter-1)*3)])/0.0982);
}
motorreset();
moveforwardextrude((Array[2+((counter-1)*3)])/0.14);
counter = counter + 1;
checker = Array[(counter-1)*3];
}



exit(0);
}
