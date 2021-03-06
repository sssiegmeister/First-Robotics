#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     driveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     driveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     driveBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     bucket1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AdvancedSensors.c"

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/c
//#pragma config(Motor,  mtr_S1_C4_1,    Collecter,            tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

task drive()
{
	while(true)
		{
       	float x1 = joystick.joy1_x1;
       	float y1 = joystick.joy1_y1;
       	float x2 = joystick.joy1_x2;
       	float y2 = joystick.joy1_y2;
       	if(abs(x1)<16)x1=0;
       	if(abs(y1)<16)y1=0;
       	if(abs(x2)<16)x2=0;
       	if(abs(y2)<16)y2=0;
				x1*=.787;
				x2*=.787;
				y1*=.787;
				y2*=.787;

			    int LF = 0;
			    int RF = 0;
			    int LR = 0;
			    int RR = 0;

				  LF += x1;
				  RF -= x1;
			    LR -= x1;
				  RR += x1;

			    LF += y1;
			    RF += y1;
			    LR += y1;
			    RR += y1;

			    LF += x2;
			    RF -= x2;
			    LR += x2;
			    RR -= x2;

       	motor[driveBL] = LR;
       	motor[driveFL] = LF;

       	motor[driveBR] = RR;
       	motor[driveFR] = RF;
				abortTimeslice();
	}
}
task bucket()
{
	while(true)
	{
		if(joy1Btn(6))
			motor[bucket1]=10;
		else if(joy1Btn(7))
			motor[bucket1]=-10;
		else
			motor[bucket1]=0;
		abortTimeslice();
	}
}
task main()
{
	getJoystickSettings (joystick);
	waitForStart();

  StartTask(drive);
  StartTask(bucket);
	while(true)
	{
		wait1Msec(1);
  }
}
