/*
 * PIDConfigureSimplePacketComsServer.h
 *
 *  Created on: Oct 19, 2018
 *      Author: hephaestus
 */

#ifndef SRC_COMS_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_
#define SRC_COMS_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_
#include <SimplePacketComs.h>
#include <PID_v1.h>

class PIDConfigureSimplePacketComsServer: public PacketEventAbstract {
	PID ** pidlist;
	int numPID;
public:
	PIDConfigureSimplePacketComsServer(int num,PID ** list);
	void event(float * buffer);

};

#endif /* SRC_COMS_PIDCONFIGURESIMPLEPACKETCOMSSERVER_H_ */
