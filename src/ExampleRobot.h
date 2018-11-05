/*
 * ExampleRobot.h
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#ifndef SRC_EXAMPLEROBOT_H_
#define SRC_EXAMPLEROBOT_H_
#include "config.h"
#include <PID_v1.h>
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include "PIDMotor.h"
#include "ServoEncoderPIDMotor.h"
#include "HBridgeEncoderPIDMotor.h"
#include <Wire.h>
#include <WiiChuck.h>
#include "GearWrist.h"
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <BNO055SimplePacketComs.h>
#include <DFRobotIRPosition.h>
#include "coms/IRCamSimplePacketComsServer.h"

enum state_t {
	Startup,
	WaitForConnect,
	StartTimer,
	readGame,
	readIMU,
	readIR,
};
#define numberOfPID  2

class ExampleRobot {
private:
	HBridgeEncoderPIDMotor motor1;
	HBridgeEncoderPIDMotor motor2;
	GearWrist * wristPtr;
	Servo tiltEyes;
	Servo jaw;
	Servo panEyes;
	bool timerStartedCheck = false;
	bool print = false;
	long lastPrint = 0;
	// Change this to set your team name
	String * name = new String("IMU-Team21");
	PID * pidList[numberOfPID];// = { &motor1.myPID, &motor2.myPID };

	#if defined(USE_GAME_CONTOL)
	Accessory control;
	#endif
	#if defined(USE_IMU)
	GetIMU * sensor;
	Adafruit_BNO055 bno;
	#endif
	#if defined(USE_WIFI)
	UDPSimplePacket coms;
	WifiManager manager;
	#endif
	#if defined(USE_IR_CAM)
	DFRobotIRPosition myDFRobotIRPosition;
	#endif
	#if defined(USE_TIMER)
	hw_timer_t * timer = NULL;
	#endif
	void runGameControl();
	void printAll();
	void fastLoop();
	void startTimer();
	void setup();
	state_t state=Startup;
public:
	ExampleRobot();
	virtual ~ExampleRobot();
	void loop();
#if defined(USE_TIMER)
	static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
#endif
};

#endif /* SRC_EXAMPLEROBOT_H_ */
