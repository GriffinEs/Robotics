#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, dgtl2,  ,               sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,            ,             tmotorVex269_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <GLOBAL2.h>

#define trc 35.0
#define dia 10.16
#define fix 1


task main(){
	SensorValue[dgtl2] =99999;
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;
	motor[port7] = 10;
	MoveDist(18,100,dia);
	motor[port6] = -100;
	wait1Msec(500);
	motor[port6] = 0;
	motor[port7] = -100;
	wait1Msec(1000);
	motor[port7] = 0;
	MoveDist(-8,100,dia);
	motor[port2] = 50;
	motor[port3] = -50;
	wait1Msec(1000);
	while(SensorValue[dgtl2] > 30 && SensorValue[dgtl2] != -1){}
	motor[port2] = 60;
	motor[port3] = -60;
	wait1Msec(600);
	motor[port4] = -100;
	motor[port5] = 100;
	wait1Msec(700);
	MoveDist(10,100,dia);
}
