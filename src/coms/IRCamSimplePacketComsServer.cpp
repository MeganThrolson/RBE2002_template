/*
 * IRCamSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "IRCamSimplePacketComsServer.h"

IRCamSimplePacketComsServer::IRCamSimplePacketComsServer(
		DFRobotIRPosition * cam) :
		PacketEventAbstract(1590) {
	camera = cam;
}

IRCamSimplePacketComsServer::~IRCamSimplePacketComsServer() {
	// TODO Auto-generated destructor stub
}

void IRCamSimplePacketComsServer::event(float * buffer) {
	for (int i = 0; i < 8; i++) {
		buffer[i] = bufferCache[i];
	}
}

void IRCamSimplePacketComsServer::loop() {
	camera->requestPosition();
	int64_t start = esp_timer_get_time();
	while (Wire.available() != 16 && ((esp_timer_get_time() - start) < 750))
		;

	if (camera->available()) {
		for (int i = 0; i < 4; i++) {
			bufferCache[(i * 2)] = camera->readX(i);
			bufferCache[(i * 2) + 1] = camera->readY(i);
		}
	}
}
