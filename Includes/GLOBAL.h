/*void PWM(int time, int port, int duration){
	for(int i = 0; i < duration/time*2; i++){
		switch(port){
			case 4: SensorValue[dgtl4] = 1; break;
			case 7: SensorValue[dgtl7] = 1; break;
			case 10: SensorValue[dgtl10] = 1; break;
		}

		wait1Msec(time/50);
		switch(port){
			case 4: SensorValue[dgtl4] = 0; break;
			case 7: SensorValue[dgtl7] = 0; break;
			case 10: SensorValue[dgtl10] = 0; break;
		}
		wait1Msec(0.1);
	}
}*/

//17.5 inches trc
// 4 in dia

void TurnInPlace(float deg, int power, float dia, float trc, float ratio){
	float degrees = deg;//*0.60-(4*sgn(degrees));
	nMotorEncoder[port1] = 0;
	nMotorEncoder[port10] = 0;

	float circ = dia*PI;

	while(true){
		bool il = false;
		bool ir = false;
		float dist1 = (nMotorEncoder[port1]*ratio)/627.2*circ;
		float dist2 = (nMotorEncoder[port10]*ratio)/627.2*circ;
		float targetdist = (trc*PI)*(degrees/360);
		if(abs(dist1) < targetdist*sgn(degrees)){
			motor[port1] = -abs(power)*sgn(degrees);
		}
		else{
			motor[port1] = 0;
			il = true;
		}

		if(abs(dist2) < targetdist*sgn(degrees)){
			motor[port10] = -abs(power)*sgn(degrees);
		}
		else{
			motor[port10] = 0;
			ir = true;
		}

		if(ir && il){
			break;
		}
	}

	motor[port10] = (abs(power)/2)*sgn(degrees);
	motor[port1] = (abs(power)/2)*sgn(degrees);
	wait1Msec(50+(power/2));
	motor[port1] = 0;
	motor[port2] = 0;
}

void MoveDist(float inc, int power, int dia, float ratio){
	float inches = inc;//-(1.5*sgn(inc));
	nMotorEncoder[port1] = 0;
	nMotorEncoder[port10] = 0;

	float circ = dia*PI;

	while(true){
		bool il = false;
		bool ir = false;
		float dist1 = (nMotorEncoder[port1]*ratio)/627.2*circ;
		float dist2 = (nMotorEncoder[port10]*ratio)/627.2*circ;
		if(abs(dist1) < inches*sgn(inches)){
			motor[port1] = -abs(power)*sgn(inches);
		}
		else{
			motor[port1] = 0;
			il = true;
		}

		if(abs(dist2) < inches*sgn(inches)){
			motor[port10] = abs(power)*sgn(inches);
		}
		else{
			motor[port10] = 0;
			ir = true;
		}

		if(ir && il){
			break;
		}
	}

	motor[port10] = -(abs(power)/2)*sgn(inches);
	motor[port1] = (abs(power)/2)*sgn(inches);
	wait1Msec(50+(power/2));
	motor[port1] = 0;
	motor[port2] = 0;
}
