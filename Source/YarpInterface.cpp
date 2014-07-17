/*
  ==============================================================================

    YarpInterface.cpp
    Created: 16 Jul 2014 1:44:43pm
    Author:  johnt_000

  ==============================================================================
*/

#include "YarpInterface.h"


YarpInterface::YarpInterface() : Thread("YarpInterface Thread") {
	yarp.init();
	
}

YarpInterface::~YarpInterface() {
	DBG("destructor called. closing port and stopping thread");
	yarpPort.close();
	yarp.fini();
	stopThread(2000);
}

bool YarpInterface::setPortName(yarp::os::ConstString name) {
	if (name[0] != '/') {
		DBG("invalid port name!");
		return false;
	}
	portName = name;
	return true;
}

void YarpInterface::run()  {
	textOutput = "yarp reader open at "+String(portName.c_str())+"\n";
	yarpPort.open(portName);
	while( !threadShouldExit()) {
		wait(1); //prevent 100% cpu use here; also assume that we won't get messages at > 1000Hz
		if (yarpPort.getPendingReads()) {
			//read port here
			yarp::os::Bottle* bot = yarpPort.read();
			for (int i=0; i<bot->size(); i++) {
				lock.enter();
				if (textOutput.length() >= 512)
					textOutput.clear(); //clear if too big.
				textOutput += bot->get(i).toString().c_str();
				lock.exit();
			}
			DBG("textOutput size = " + String(textOutput.length()));
			sendChangeMessage();
		}
	}
	yarpPort.close();
	DBG("yarp read thread exiting...");
}

