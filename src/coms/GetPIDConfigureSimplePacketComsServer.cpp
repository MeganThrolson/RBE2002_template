/*
 * PIDConfigureSimplePacketComsServer.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#include "GetPIDConfigureSimplePacketComsServer.h"

GetPIDConfigureSimplePacketComsServer::GetPIDConfigureSimplePacketComsServer(int num,
		PID ** list) :
		PacketEventAbstract(1857) {
	numPID = num;
	pidlist = list;

}

void GetPIDConfigureSimplePacketComsServer::event(float * buffer){
	  for(int i=0;i<numPID;i++){
		  PID * current = pidlist[i];
		  buffer[(i*3)+0]=current->GetKp();
		  buffer[(i*3)+1]=current->GetKi();
		  buffer[(i*3)+2]=current->GetKd();
	  }

}

