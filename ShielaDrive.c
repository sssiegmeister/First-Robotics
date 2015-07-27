#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     colorSensor,    sensorCOLORFULL)
#pragma config(Sensor, S4,     sideTouch,      sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     Shoulder,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Spin,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     driveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     driveR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     driveL,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AdvancedSensors.c"

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/c
//#pragma config(Motor,  mtr_S1_C4_1,    Collecter,            tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

int soft = 0;
task drive(){
	while(true){
       	float x1 = joystick.joy1_x1;
       	float y1 = joystick.joy1_y1;
       	float x2 = joystick.joy1_x2;
       	float y2 = joystick.joy1_y2;
       	if(abs(x1)<12)x1=0;
       	if(abs(y1)<12)y1=0;
       	if(abs(x2)<12)x2=0;
       	if(abs(y2)<12)y2=0;
       	//15.78*(1.0158)^x
				x1*=.787;
				x2*=.787;
				y1*=.787;
				y2*=.787;
        /*x1 = 15.78*pow(1.0158,x1);
       	x2 = 15.78*pow((1.0158),x2);
       	y1 = 15.78*pow((1.0158),y1);
       	y2 = 15.78*pow( (1.0158),y2);*/

       	//

				//x1 = //pow((x1/divider),3)/multiply;
				//x2 = //pow((x2/divider),3)/multiply;
				//y1 = //pow((y1/divider),3)/multiply;
				//y2 = //pow((y2/divider),3)/multiply;


			  string where;





			    int LF = 0; //Left-front
			    int RF = 0; //Right-front
			    int LR = 0; //Left-rear
			    int RR = 0; //Right-rear

			    // Handle StrafiRightFrontng Movement
				  LF += x1;
				  RF -= x1;
			    LR += x1;
				  RR -= x1;


			    //Handle Regular Movement

			    LF += y1;
			    RF += y1;
			    LR += y1;
			    RR += y1;

			    //Handle Turning Movement

			    LF += x2;
			    RF -= x2;
			    LR -= x2;
			    RR += x2;

			    // Apply Finished values to motors.






       	motor[driveL] = LR;
       	motor[driveFL] = LF;

       	motor[driveR] = RR;
       	motor[driveFR] = RF;
       	//wait1Msec(10);
				abortTimeslice();
	}
}
int wristLoc = 50;
task wristControl(){
	while(true){
		//nxtDisplayClearTextLine(0);
			//	nxtDisplayString(0, "%d", wristLoc);
       	if(joy1Btn(05)){
					//if(wristLoc>=50){
						wristLoc-=1;
					//}
				}
				else if(joy1Btn(07)){
					//if(wristLoc<=150){
						wristLoc+=1;
					//}
				}
				//servo[wrist] = wristLoc;
				wait1Msec(50);
	}
}
bool sto;
int lastShoulder = 100;
int shoulderRate = 0;
bool lift = false;

task shoulderControl(){
	while(true){



	lastShoulder = nMotorEncoder[Shoulder];
	while(true){
		shoulderRate = nMotorEncoder[Shoulder]-lastShoulder;


		if(joy1Btn(06)&&nMotorEncoder[Shoulder]<1000){
					if(shoulderRate<20){
						motor[Shoulder] = 80;
					}
					else{
						motor[Shoulder] = 40;
					}
					sto = true;
		}

		else if(joy1Btn(08)){
					sto = true;
					string temp;
					sprintf(temp, "Speed: %d", shoulderRate);
					nxtDisplayClearTextLine(0);
					nxtDisplayString(0,temp);
					sprintf(temp, "This: %d", nMotorEncoder[Shoulder]);
					nxtDisplayClearTextLine(1);
					nxtDisplayString(1,temp);
					sprintf(temp, "Last: %d", lastShoulder);
					nxtDisplayClearTextLine(2);
					nxtDisplayString(2,temp);
					if(shoulderRate>-1){
						motor[Shoulder] = -20;
					}
					else if(shoulderRate<-10){
						motor[Shoulder] = 25;
					}


		}
		else if(sto){

			if(nMotorEncoder[Shoulder]>957) motor[Shoulder] = 15;
			else motor[Shoulder] = 20;

			sto=false;
		}
		else{
			motor[Shoulder] = 15;
		}
		lastShoulder = nMotorEncoder[Shoulder];
		wait1Msec(10);
	}

	wait1Msec(100);
	}
}
task liftControl(){
	while(true){

	if(joystick.joy1_TopHat==0){
		//wristLoc = 124;
		//stopTask(shoulderControl);
		motor[Lift]=80;
	}
	else if(joystick.joy1_TopHat==4){
		//wristLoc = 124;
		//StartTask(shoulderControl);
		motor[Lift]=-80;
	}
	else{
		motor[Lift]=0;
	}
	wait1Msec(10);
	abortTimeslice();
	}
}
int LEVEL_DEBUG = 0;
int LEVEL_WARN = 1;
int LEVEL_ERROR = 2;

bool spinning = false;
task handControl(){
	while(true){
		if(spinning){
			if(joy1Btn(01)){
					motor[spin] = -100;
			}
			else{
					motor[spin] = 100;
			}
		}
		else motor[spin] = 0;
		if(joy1Btn(09)){
			while(joy1Btn(09)){
				wait1Msec(10);
			}
			spinning = !spinning;
		}
		wait1Msec(10);
		abortTimeslice();

	}
}
task main(){
	nMotorEncoder[Shoulder]=0;
	//1const int THRESHOLD = 5;
	getJoystickSettings (joystick);

	//bool turbo = false;
	//


	//servo[Bro] = 5000;
	waitForStart();   // wait for start of tele-op phase
	//servo[armRelease] = 0;

	//servo[binlift] = 30;
	//const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"


  //SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor

  //Initial Setup


  /*
 		Setup arm at correct angles
  */

	//servo[hand] = 50;

  StartTask(drive,10);
  //StartTask(wristControl);
  StartTask(handControl);
  StartTask(shoulderControl);
  StartTask(liftControl);
	while(true)
	{

		wait1Msec(100);
  }
}
