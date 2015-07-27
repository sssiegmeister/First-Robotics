#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     multiplexor,    sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     seeker,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     driveL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    preLoad,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-touchmux.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//void initializeRobot()
//{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  //return;
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	int speed=-15;
	int acS1, acS2, acS3, acS4, acS5 = 0;
	bool finished = false;

  waitForStart();

  wait1Msec(10000);

  ClearTimer(T1);

  while (SensorValue[multiplexor]!=4||time1[T1]<1000)
  {
  	motor[driveL]=speed;
  	motor[driveR]=speed;
  	HTIRS2readAllACStrength(seeker, acS1, acS2, acS3, acS4, acS5 );
  	if((acS5-acS4)<30&&(acS5+acS4)>70&&finished==false)
  	{
  		motor[driveL]=speed;
  		motor[driveR]=speed;
  		wait1Msec(1750);
  		motor[driveL]=0;
  		motor[driveR]=0;
  		servo[preLoad]=0;
  		wait10Msec(100);
  		servo[preLoad]=255;
  		finished = true;
  		speed = speed*-1;
  		wait1Msec(500);
  	}
  }
  motor[driveL]=-50;
  motor[driveR]=-50;
  wait1Msec(500);
  motor[driveL]=0;
  motor[driveR]=255;
  wait1Msec(1500);
  motor[driveL]=100;
  motor[driveR]=100;
  wait1Msec(1000);
  motor[driveL]=0;
  motor[driveR]=255;
  wait1Msec(1000);
  motor[driveL]=100;
  motor[driveR]=100;
  wait1Msec(2000);
}
