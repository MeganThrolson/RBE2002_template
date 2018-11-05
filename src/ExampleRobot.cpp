/*
 * ExampleRobot.cpp
 *
 *  Created on: Nov 5, 2018
 *      Author: hephaestus
 */

#include "ExampleRobot.h"

static GearWrist * wristPtrLocal;
#if defined(USE_TIMER)
portMUX_TYPE ExampleRobot::timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&ExampleRobot::timerMux);
	wristPtrLocal->loop();
	portEXIT_CRITICAL_ISR(&ExampleRobot::timerMux);

}
#endif

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

ExampleRobot::ExampleRobot() {
	// TODO Auto-generated constructor stub
	pidList[0] = &motor1.myPID;
	pidList[1] = &motor2.myPID;
	wristPtr = NULL;
	state = Startup;
#if defined(USE_IMU)
	sensor = NULL;
#endif
}

ExampleRobot::~ExampleRobot() {
	// TODO Auto-generated destructor stub
}

void ExampleRobot::setup() {
#if defined(USE_WIFI)
	manager.setup();
#else
	Serial.begin(115200);
#endif
	delay(100);
	motor1.attach(2, 15, 36, 39);
	motor2.attach(16, 4, 34, 35);
	Serial.println("Starting Motors: 4");

	// Create a module to deal with the demo wrist bevel gears
	wristPtr = new GearWrist(&motor1, //right motor
			&motor2, // left motor
			16.0 * // Encoder CPR
					50.0 * // Motor Gear box ratio
					2.5347 * // Wrist gear stage ratio
					(1.0 / 360.0) * // degrees per revolution
					motor1.encoder.countsMode, // full quadrature, 4 ticks be encoder count, half is 2 and single mode is one
			0.8932); // ratio of second stage to first stage
	wristPtrLocal = wristPtr;
	// Set up digital servos
	panEyes.setPeriodHertz(330);
	panEyes.attach(18, 1000, 2000);
	jaw.setPeriodHertz(330);
	jaw.attach(19, 1000, 2000);
	tiltEyes.setPeriodHertz(330);
	tiltEyes.attach(23, 1000, 2000);
#if defined(USE_GAME_CONTOL)
	control.begin();
	control.readData();    // Read inputs and update maps
#endif
//	// Create sensors and servers
#if defined(USE_IMU)
	sensor = new GetIMU();
	/* Initialise the sensor */
	if (!bno.begin()) {
		/* There was a problem detecting the BNO055 ... check your connections */
		Serial.print(
				"Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
		delay(1000);
		while (1)
			;
	}

	delay(1000);
	bno.setExtCrystalUse(true);
	sensor->startSensor(&bno);
#endif
#if defined(USE_IR_CAM)
	myDFRobotIRPosition.begin();
#endif
#if defined(USE_WIFI)
	// Attach coms
#if defined(USE_IMU)
	coms.attach(sensor);
#endif
#if defined(USE_IR_CAM)
	coms.attach(new IRCamSimplePacketComsServer(&myDFRobotIRPosition));
#endif
	coms.attach(new NameCheckerServer(name));
#endif
	// PID control loop timer
}

void ExampleRobot::loop() {

	fastLoop();

	if (millis() - lastPrint > 5) {

		lastPrint = millis();

		switch (state) {
		case Startup:
			setup();
			state = StartTimer;
			break;
		case StartTimer:
			startTimer();
			state = readGame;
			break;
		case readGame:
			runGameControl();
			state = readIMU;
			break;
		case readIMU:
#if defined(USE_IMU)
#if defined(USE_TIMER)
			portENTER_CRITICAL(&timerMux);
#endif
			sensor->loop();
#if defined(USE_TIMER)
			portEXIT_CRITICAL(&timerMux);
#endif
			sensor->print();
#endif
			state = readIR;
			break;
		case readIR:
#if defined(USE_IR_CAM)
#if defined(USE_TIMER)
			portENTER_CRITICAL(&timerMux);
#endif
			myDFRobotIRPosition.requestPosition();
			myDFRobotIRPosition.available();
#if defined(USE_TIMER)
			portEXIT_CRITICAL(&timerMux);
#endif
#endif
			state = readGame;    // loop back to start of sensors
			break;

		}

		printAll();
	}
}

void ExampleRobot::startTimer() {
#if defined(USE_TIMER)
	if (!timerStartedCheck) {
		timerStartedCheck = true;

		timer = timerBegin(3, 80, true);
		timerAttachInterrupt(timer, &onTimer, true);
		timerAlarmWrite(timer, 1000, true); // 1khz
		timerAlarmEnable(timer);
		Serial.println("Timer started");

	}
#endif
}

void ExampleRobot::fastLoop() {
#if defined(USE_WIFI)
	manager.loop();
	if (manager.getState() == Connected)
		coms.server();
	else {
		return;
	}
#endif
#if !defined(USE_TIMER)
	wristPtr->loop();
#endif
}

void ExampleRobot::runGameControl() {
#if defined(USE_GAME_CONTOL)
	control.readData(); // Read inputs and update maps

	float Servo1Val = mapf((float) control.values[1], 0.0, 255.0, -15.0, 15.0);
	float Servo3Val = mapf((float) control.values[0], 0.0, 255.0, -60.0, 60.0); // z button
	int panVal = map(control.values[2], 0, 255, 35, 148);
	int jawVal = map(control.values[5] > 0 ? 0 :    // Upper button pressed
			(control.values[18] > 0 ? 255 :    // Lower button pressed
					128)    //neither pressed
			, 0, 255, 80, 160);
	int tiltVal = map(control.values[3], 0, 255, 24, 120);    // z button
#if defined(USE_TIMER)
	portENTER_CRITICAL(&timerMux); // Since PWM is called inside of the interrupt, this needs to wrap all other PWM's
#endif
	panEyes.write(panVal);
	tiltEyes.write(tiltVal);
	jaw.write(jawVal);
	wristPtr->setTarget(Servo1Val, Servo3Val);
#if defined(USE_TIMER)
	portEXIT_CRITICAL(&timerMux); // Since PWM is called inside of the interrupt, this needs to wrap all other PWM's
#endif
#endif

}
void ExampleRobot::printAll() {
	if (print) {
//			Serial.println(
//					" Pan  = " + String(panVal) + " tilt = " + String(tiltVal));
		Serial.println(
				" Angle of A = " + String(wristPtr->getA()) + " Angle of B = "
						+ String(wristPtr->getB()));
//			Serial.println(
//					" Tick of L = " + String((int32_t) motor1.getPosition())
//							+ " Angle of R = "
//							+ String((int32_t) motor2.getPosition()));
//			for (int i = 0; i < WII_VALUES_ARRAY_SIZE; i++) {
//				Serial.println(
//						"\tVal " + String(i) + " = "
//								+ String((uint8_t) control.values[i]));
//			}
//
//			if (!myDFRobotIRPosition.available()) {
//				for (int i = 0; i < 4; i++) {
//					Serial.print(myDFRobotIRPosition.readX(i));
//					Serial.print(",");
//
//					Serial.print(myDFRobotIRPosition.readY(i));
//					Serial.print(";");
//				}
//				Serial.println();
//
//			}
	}
}
