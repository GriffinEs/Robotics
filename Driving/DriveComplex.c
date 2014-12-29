
bool arcade = false; // Whether to be in arcade mode or not
bool oldbtn = false; 		// the last value of vexRT[Btn8D] to help with switching arcade mode


void ArcadeFlip(bool btn, bool old){		// function to switch arcade mode
	if(btn && !old && arcade){ 						// if the button is on and it wasn't on before and arcade is on then
		arcade = false;											// turn arcade off.
	} else if(btn && !old && !arcade){		// if the button is on and it wasn't on before and arcade is off then
		arcade = true;											// turn arcade on.
	}
}


task killswitch(){ // The task to listen for the killswitch to be pressed and stop the program if it is.
	while(1){ 									// do this forever, unless it's stopped by itself
		if(SensorValue[dgtl1]){		// If the killswitch (port 1) is pressed, then
			stopAllTasks();					// stop all tasks (this one and task main).
		}
	}
}

task openclaw(){				// the task to open the claw
	motor[port7] = 127;		// make the claw motor open
	wait1Msec(2000);			// wait for two seconds
	motor[port7] = 0;			// stop opening the claw so that the motor won't get stripped
}

task closeclaw(){				// the task to close the claw!
	motor[port7] = -127;	// close the claw fast at first
	wait1msec(1500);			// for 1.5 seconds, and then
	motor[port7] = -100;	// constantly close the claw to hold a cube at a lower power (no gear strip)
}

task main(){
	startTask(killswitch); // Start the task to listen for killswitch press

	while(1){ // Do this forever, unless the task is stopped.

		if(arcade){ 	//................................ the code that runs the joysticks is dependant on arcade mode.
			motor[port2] = (vexRT[Ch1]-vexRT[Ch2]); 		// left wheel
			motor[port3] = -(vexRT[Ch1]+vexRT[Ch2]); 	// right wheel
			motor[port4] = -(vexRT[Ch3]); 							// left arms
			motor[port5] = (vexRT[Ch3]); 								// right arms
		} else { 			//................................ if it's not in arcade mode...
			motor[port2] = vexRT[Ch3];									// left wheel to left joystick
			motor[port3] = vexRT[Ch2];									// right wheel to right joystick
			motor[port4] = (vexRT[Btn6U]-vexRT[Btn5D])*127;			// left arms to a button
			motor[port5] = -(vexRT[Btn6U]-vexRT[Btn5D])*127;		// right arms to a button
		} 						//........................................ the buttons below don't change.
		motor[port6] = -(vexRT[Btn5U]*127-vexRT[Btn5D]*127); 	// claw actuator

		if(vexRT[Btn7L] && !vexRT[Btn7R]){					// if 7l is pressed and 7r is not
			stopTask(openclaw);												// stop trying to open the claw
			stopTask(closeclaw);											// also kill previous instances of this task
			startTask(closeclaw);											// and start closing it.
		} else if(vexRT[Btn7R] && !vexRT[Btn7L]){ 	// otherwise, if 7r is on and 7l isn't..
			stopTask(closeclaw);											// stop the closeclaw task
			stopTask(openclaw);												// also kill previous instances of this task
			startTask(openclaw);											// then start a new openclaw task
		}

		ArcadeFlip(vexRT[Btn8D], oldbtn);	// Function to switch to and from arcade mode
		oldbtn = vexRT[Btn8D]; 						// Set the value of oldbtn to the current vexRT[Btn8D] so it can be compared to the one
	}																		// on the next cycle.
}
