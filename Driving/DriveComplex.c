#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port7,            ,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool arcade = false;		// Whether to be in arcade mode or not
bool clawopen = false;	// Whether or not the claw is open
bool oldcl = false;			// was the claw opened last cycle?
bool oldbtn = false; 		// the last value of vexRT[Btn8D] to help with switching arcade mode
bool oldbtn2 = false;		// the last value of vexRT[Btn7R] to help with opening and closing the
int offset = 0;


void ArcadeFlip(bool btn, bool old){		// function to switch arcade mode
	if(btn && !old && arcade){ 						// if the button is on and it wasn't on before and arcade is on then
		arcade = false;											// turn arcade off.
	} else if(btn && !old && !arcade){		// if the button is on and it wasn't on before and arcade is off then
		arcade = true;											// turn arcade on.
	}
}


void PIDMotorSync(int armpos,int clawpos){
	clawpos *= 2;
	motor[port6] = (offset-clawpos+armpos);
}


task killswitch(){ 						// The task to listen for the killswitch to be pressed and stop the program if it is.
	while(1){ 									// do this forever, unless it's stopped by itself
		if(SensorValue[dgtl1]){		// If the killswitch (port 1) is pressed, then
			stopAllTasks();					// stop all tasks (this one and task main).
		}
	}
}

task claw(){												// the task to open and close the claw
	if(clawopen){											// if the claw should be open
		motor[port7] = -127;						// Open the claw
		wait1Msec(500);									// wait for it to open fully
		motor[port7] = 0;								// turn off the motor
	} else if(!clawopen){							// but if the claw isn't supposed to be open (so it should close)
		motor[port7] = 127;							// close the claw fast
		wait1Msec(500);									// wait for it to close
		motor[port7] = 50;							// then apply a constant indefinitely to hold the thing
	}
}

task main(){
	startTask(killswitch); // Start the task to listen for killswitch press

	nMotorEncoder[port5] = 0;
	nMotorEncoder[port6] = 0;

	while(1){ // Do this forever, unless the task is stopped.

		if(arcade){ 	//................................ the code that runs the joysticks is dependant on arcade mode.
			motor[port2] = (vexRT[Ch2]+vexRT[Ch1])*0.9; 		// left wheel
			motor[port3] = (vexRT[Ch2]-vexRT[Ch1])*0.9; 		// right wheel
			motor[port4] = -(vexRT[Ch3]); 							// left arms
			motor[port5] = (vexRT[Ch3]); 								// right arms
		} else { 			//................................ if it's not in arcade mode...
			motor[port2] = vexRT[Ch3]*0.9;									// left wheel to left joystick
			motor[port3] = vexRT[Ch2]*0.9;									// right wheel to right joystick
			motor[port4] = -(vexRT[Btn6U]-vexRT[Btn6D])*127;			// left arms to a button
			motor[port5] = (vexRT[Btn6U]-vexRT[Btn6D])*127;				// right arms to a button
		} 						//........................................ the buttons below don't change.
		offset -= (vexRT[Btn5U]-vexRT[Btn5D]);							 		// claw actuator
		PIDMotorSync(nMotorEncoder[port5],nMotorEncoder[port6]);



		if(vexRT[Btn7R] && !oldcl && clawopen){						// if 7l is pressed and the claw mode wasn't switched last cycle
			clawopen = false;																// make it false and close the claw
			oldcl = true;																		// set the oldcl variable to true;
			startTask(claw);	// do the claw
		} else if(vexRT[Btn7R] && !oldcl && !clawopen){		// if 7r is pressed and the claw wasn't switched
			clawopen = true;																// make it open
			oldcl = true;																		// set oldcl to true
			startTask(claw);	// do the claw
		}
		if(!vexRT[Btn7R] && oldcl){												// if no longer holding btn7r and oldcl is true
			oldcl = false;																	// make oldcl false
		}





		ArcadeFlip(vexRT[Btn8D], oldbtn);	// Function to switch to and from arcade mode
		oldbtn2 = vexRT[Btn7R];						// Set oldbtn2 to the value of vexRT[btn8d] for the next cycle
		oldbtn = vexRT[Btn8D]; 						// Set the value of oldbtn to the current vexRT[Btn8D] so it can be compared to the one
	}																		// on the next cycle.
}
