#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, dgtl2,  ,               sensorSONAR_cm)
#pragma config(Sensor, dgtl4,  ,               sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,            ,             tmotorVex269_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <GLOBAL2.h>

#define trc 35.0
#define dia 10.16
#define fix 1


task main(){
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;
	nMotorEncoder[port5] = 0;
	nMotorEncoder[port5] = 0;
	nMotorEncoder[port5] = 0;
	wait1Msec(30);
	MoveDist(-10,100,dia);
	MoveDist(7,100,dia);
	motor[port4] = -100;
	motor[port5] = 100;
	motor[port6] = 55;
	motor[port7] = -50;
	while(nMotorEncoder[port5] < 380){} //raise arm
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = -10;
	motor[port2] = -50;
	motor[port3] = 50;
	wait1Msec(300);
	motor[port7] = 0;
	while(SensorValue[dgtl4] > 30 || SensorValue[dgtl2] == -1){} // turn to thing
	motor[port2] = 60;
	motor[port3] = -60;
	wait1Msec(50);
	motor[port2] = 30;
	motor[port3] = 30;
	while(SensorValue[dgtl4] > 4 || SensorValue[dgtl2] == -1){} //move to thing
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port7] = 100;
	wait1Msec(500);

	motor[port7] = 5;
	motor[port4] = -100;
	motor[port5] = 100;
	motor[port6] = -100;
	motor[port2] = -60;
	motor[port3] = -60;

	while(nMotorEncoder[port5] < 500){} // up
	wait1Msec(200);

	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port2] = 50;
	motor[port3] = -50;
	wait1Msec(500);
	while(SensorValue[dgtl2] > 40 && SensorValue[dgtl2] != -1){} // turn to base
	wait1Msec(50);
	motor[port2] = -10;
	motor[port3] = 10;
	wait1Msec(200);
	motor[port2] = 40;
	motor[port3] = 40;
	motor[port6] = 60;

	while(SensorValue[dgtl2] > 23 && SensorValue[dgtl2] != -1){} // move towards base

	motor[port2] = 0;
	motor[port3] = 0;
	wait1Msec(100);
	motor[port7] = 5;
	motor[port4] = 50;
	motor[port5] = -50;
	motor[port6] = 120;

	while(nMotorEncoder[port5] > 100){} // lower

	motor[port6] = 0;
	motor[port7] = -120;
	wait1Msec(300);
	MoveDist(-10,100,dia);
	motor[port6] = 0;


	motor[port4] = -100;
	motor[port5] = 100;
	motor[port6] = -50;
	while(nMotorEncoder[port5] < 300){}
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;

	motor[port2] = -40;
	motor[port3] = 40;
	motor[port7] = 0;
	wait1Msec(1000);
	while(SensorValue[dgtl4] > 30 || SensorValue[dgtl2] == -1){}
	wait1Msec(100);
	motor[port2] = 60;
	motor[port3] = -60;
	wait1Msec(100);
	motor[port2] = 30;
	motor[port3] = 30;
	while(SensorValue[dgtl4] > 4 || SensorValue[dgtl2] == -1){}
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port7] = 100;
	wait1Msec(500);
}
