#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,            ,             tmotorVex269_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_3)


task main(){
	nMotorEncoder[port5] = 0;
	/*while(1){
		motor[port4] = -vexRT[Ch2];
		motor[port5] = vexRT[Ch2];
		writeDebugStreamLine("%d", nMotorEncoder[port5]);
	}*/
	motor[port4] = -100;
	motor[port5] = 100;
	while(nMotorEncoder[port5] < 450){}
}
