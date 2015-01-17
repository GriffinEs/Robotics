#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
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
	nMotorEncoder[port2] = 0;
	nMotorEncoder[port3] = 0;
	MoveDist(153,100,dia);             // forward 4.5 feet
	TurnRobot(90,100,dia,trc,fix);     // turns 90 degrees right
	MoveDist(85,100,dia);              // forward a bit less than 2 feet
	TurnRobot(90,100,dia,trc,fix);     // turns 90 degrees right
	MoveDist(122,100,dia);             // forward 3 feet
	MoveDist(-61,100,dia);             // backwards
}
