
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

task main(){
	startTask(killswitch); // Start the task to listen for killswitch press

	while(1){ // Do this forever, unless the task is stopped.

		if(arcade){ 	//................................ the code that runs the joysticks is dependant on arcade mode.
			motor[port1] = (vexRT[Ch1]-vexRT[Ch2]); 		// left wheel
			motor[port10] = -(vexRT[Ch1]+vexRT[Ch2]); 	// right wheel
			motor[port2] = -(vexRT[Ch3]); 							// left arms
			motor[port3] = (vexRT[Ch3]); 								// right arms
		} else { 			//................................ if it's not in arcade mode...
			motor[port1] = vexRT[Ch3];									// left wheel to left joystick
			motor[port10] = vexRT[Ch2];									// right wheel to right joystick
			motor[port2] = (vexRT[Btn6U]-vexRT[Btn5D])*127;			// left arms to a button
			motor[port3] = -(vexRT[Btn6U]-vexRT[Btn5D])*127;		// right arms to a button
		} 						//........................................ the buttons below don't change.
		motor[port4] = -(vexRT[Btn5U]*127-vexRT[Btn5D]*127); 	// claw actuator
		motor[port5] = (vexRT[Btn7L]*127-vexRT[Btn7R]*127); 	// the claaaaw

		ArcadeFlip(vexRT[Btn8D], oldbtn);	// Function to switch to and from arcade mode
		oldbtn = vexRT[Btn8D]; 						// Set the value of l to the current vexRT[Btn8D] so it can be compared to the one
	}																// on the next cycle.

	motor[port2] = 0; // if the kill switch is pressed, STOP EVERYTHING
	motor[port9] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
}
