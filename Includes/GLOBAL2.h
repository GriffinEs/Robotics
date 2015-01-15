

void TurnRobot(float deg, int power, float dia, float trc, float fix){
	float wc = PI*dia;
	float rc = PI*trc;
	deg = deg*fix;
	float wheeldist = (rc*deg)/360.0;
	float turnleft = sgn(deg);
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;

	bool left = false;
	bool right = false;

	while(left == false && right == false){
		float distL = abs(nMotorEncoder[port2]/627.2)*wc;
		float distR = abs(nMotorEncoder[port3]/627.2)*wc;

		if(distL >= wheeldist){
			left = true;
			motor[port2] = 0;
		} else {
			motor[port2] = abs(power)*turnleft;
		}

		if(distR >= wheeldist){
			 right = true;
			 motor[port3] = 0;
		} else {
			motor[port3] = -abs(power)*turnleft;
		}

	}

	motor[port3] = 20*turnleft;
	motor[port2] = -20*turnleft;
	wait1Msec(100);
	motor[port3] = 0;
	motor[port2] = 0;
}

void MoveDist(float cm, int power, int dia){
	float wc = PI*dia;
	int back = sgn(cm);
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;

	bool left = false;
	bool right = false;

	while(left == false && right == false){
		float distL = abs(nMotorEncoder[port2]/627.2)*wc;
		float distR = abs(nMotorEncoder[port3]/627.2)*wc;

		if(distL >= cm){
			left = true;
			motor[port2] = 0;
		} else {
			motor[port2] = abs(power)*back;
		}

		if(distR >= cm){
			right = true;
			motor[port3] = 0;
		} else {
			motor[port3] = abs(power)*back;
		}
	}

	motor[port2] = -10*back;
	motor[port3] = -10*back;
	wait1Msec(100);
	motor[port2] = 0;
	motor[port3] = 0;
}
