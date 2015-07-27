#pragma config(Sensor, S1,     eye,            sensorI2CHiTechnicColor)
#pragma config(Sensor, S4,     com,            sensorI2CCustom)
#pragma config(Motor,  motorB,          driveL,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          driveR,        tmotorNXT, PIDControl, encoder)
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
#include "AdvancedSensors.c"


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
	while(true)
	{
		int red=0;
		int blue=0;
		int green=0;

		getRGB(eye, red, green, blue);
		nxtDisplayTextLine(1, "Red:    %d",  red);
		nxtDisplayTextLine(2, "Green:  %d",  green);
		nxtDisplayTextLine(3, "Blue:   %d",  blue);
		if(green!= 255)
		{
			motor[driveL]=25;
  	motor[driveR]=25;
  	getRGB(eye, red, green, blue);
		nxtDisplayTextLine(1, "Red:    %d",  red);
		nxtDisplayTextLine(2, "Green:  %d",  green);
		nxtDisplayTextLine(3, "Blue:   %d",  blue);
	}
		else if(green == 255)
		{
  	motor[driveL]=10;
  	motor[driveR]=-10;
  		getRGB(eye, red, green, blue);
		nxtDisplayTextLine(1, "Red:    %d",  red);
		nxtDisplayTextLine(2, "Green:  %d",  green);
		nxtDisplayTextLine(3, "Blue:   %d",  blue);
  	wait1Msec(1);
  }else{
 	 	motor[driveL]=-25;
  	motor[driveR]=25;
  	getRGB(eye, red, green, blue);
		nxtDisplayTextLine(1, "Red:    %d",  red);
		nxtDisplayTextLine(2, "Green:  %d",  green);
		nxtDisplayTextLine(3, "Blue:   %d",  blue);
  }
}
}
