#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     driveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     driveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     driveBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     arm,           tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     pulley,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    door,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    sweep,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AdvancedSensors.c"

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/c
//#pragma config(Motor,  mtr_S1_C4_1,    Collecter,            tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

bool open=true;

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
			    int LB = 0;
			    int RB = 0;

				  LF += x1;
				  RF -= x1;
			    LB -= x1;
				  RB += x1;

			    LF += y1;
			    RF += y1;
			    LB += y1;
			    RB += y1;

			    LF += x2;
			    RF -= x2;
			    LB += x2;
			    RB -= x2;

       	motor[driveBL] = LB;
       	motor[driveFL] = LF;
       	motor[driveBR] = RB;
       	motor[driveFR] = RF;
				abortTimeslice();
	}
}
task bucket()
{
	while(true)
	{
		if(joy1Btn(6))
		{
			motor[arm]=40;
			wait10Msec(1);
		}
		else if(joy1Btn(8))
		{
			motor[arm]=-40;
			wait10Msec(1);
		}
		else
		{
			motor[arm]=0;
			wait10Msec(1);
		}
		abortTimeslice();
	}
}
task sweeping()
{
	while(true)
	{
		if(joy1Btn(2))
		{
			servo[door]=10;
		}
		else if(joy1Btn(1))
		{
			servo[door]=0;
		}
		abortTimeslice();
	}
}
task release()
{
	while(true)
	{
		if(joy1Btn(4)&&open==true)
		{
			servo[door]=255;
			wait10Msec(50);
			open=false;
		}
		if(joy1Btn(4)&&open==false)
		{
			servo[door]=0;
			wait10Msec(50);
			open=true;
		}
		abortTimeslice();
	}
}
task raising()
{
	while(true)
	{
		if(joy1Btn(5))
		{
			motor[pulley]=75;
		}
		else if(joy1Btn(7))
		{
			motor[pulley]=-10;
		}
		else
		{
			motor[pulley]=10;
		}
		abortTimeslice();
	}
}
task main()
{
	getJoystickSettings (joystick);
	waitForStart();

  StartTask(drive);
  StartTask(raising);
  StartTask(bucket);
  StartTask(release);
  StartTask(sweeping);
	while(true)
	{
		wait1Msec(1);
  }
}
