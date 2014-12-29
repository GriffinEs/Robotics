
task main(){
	while(!SensorValue(dgtl1)){

		motor[port2] = (vexRT[Ch1]-vexRT[Ch2]); // left wheel
		motor[port9] = -(vexRT[Ch1]+vexRT[Ch2]); // right wheel
		motor[port4] = -(vexRT[Ch3]); // first layer of arms
		motor[port5] = -(vexRT[Ch3]); // other arm motors
		motor[port6] = -(vexRT[Btn5U]*127-vexRT[Btn5D]*127); // top left servo motors
		motor[port7] = (vexRT[Btn5U]*127-vexRT[Btn5D]*127); // top right servo motors
		motor[port8] = (vexRT[Btn6U]*127-vexRT[Btn6D]*127); // the claaaaw
	}

	motor[port2] = 0;
	motor[port9] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
}
