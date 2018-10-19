/*
 * PIDMotor.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#include "PIDMotor.h"
#include <Arduino.h>
PIDMotor::PIDMotor() :
		myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT) {

}

PIDMotor::~PIDMotor() {
	// TODO Auto-generated destructor stub
}
void PIDMotor::pidinit() {
	myPID.SetMode(MANUAL);
	myPID.SetMode(AUTOMATIC);
	myPID.SetOutputLimits(-PID_OUTPUT_COMPUTE_RANGE, PID_OUTPUT_COMPUTE_RANGE);
	myPID.SetTunings(Kp, Ki, Kd, P_ON_E);
	myPID.SetSampleTime(1);
}

void PIDMotor::loop() {
	Input = (float) getPosition();
	bool thisErrPositive = Input > 0;
	if (thisErrPositive != lastErrPositive) {
		// strobe mode to trigger zeroing of the Integral buffer
		// In case of passing zero clear the integral sum
		Output = 0;
		myPID.SetMode(MANUAL);
		myPID.SetMode(AUTOMATIC);
	}
	lastErrPositive = thisErrPositive;
	if (myPID.Compute()) {
		int out = map(Output, -PID_OUTPUT_COMPUTE_RANGE,
				PID_OUTPUT_COMPUTE_RANGE, getOutputMin(), getOutputMax());
		setOutput(out);
	}

}
void PIDMotor::overrideCurrentPosition(int64_t val) {
	overrideCurrentPositionHardware(val);

	setSetpoint(val);
	myPID.SetTunings(Kp, Ki, Kd, P_ON_E);
	// strobe mode to trigger zeroing of the Integral buffer
	Output = 0;
	myPID.SetMode(MANUAL);
	myPID.SetMode(AUTOMATIC);
}
void PIDMotor::setSetpoint(int64_t val) {
	Setpoint = (float) val;
}
void PIDMotor::SetTunings(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	overrideCurrentPosition(getPosition());
}
