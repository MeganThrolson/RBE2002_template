/*
 * GetPIDData.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: hephaestus
 */

#include "GetPIDData.h"

GetPIDData::~GetPIDData() {
	// TODO Auto-generated destructor stub
}

GetPIDData::GetPIDData(int num, PIDMotor ** list) :
		PacketEventAbstract(1910) {
	numPID = num;
	pidlist = list;

}

void GetPIDData::event(float * buffer) {
	buffer[0] = numPID;
	for (int i = 0; i < numPID; i++) {
		PIDMotor * current = pidlist[i];
		buffer[i * 3 + 1 + 0] = current->getSetPoint();
		buffer[i * 3 + 1 + 1] = current->getPosition();
	}

}

