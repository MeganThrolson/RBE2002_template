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

void IRCamSimplePacketComsServer::event(float * buffer){
	  if (camera->available()) {
	    for (int i=0; i<4; i++) {
	    	buffer[(i*2)]=camera->readX(i);
	    	buffer[(i*2)+1]=camera->readY(i);
	    }
	  }
}

