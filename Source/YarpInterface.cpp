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

bool YarpInterface::setNSAddress(yarp::os::ConstString addr) {
	//TODO: check valid IP?
	nsIPAddr = addr;

	return true;
}

void YarpInterface::run()  {

	textOutput = "using nameserver at " + String(nsIPAddr.c_str())
				+ "\nyarp reader open at " +String(portName.c_str())+"\n";
	nameConfig.setManualConfig(nsIPAddr, 10000);
	yarpPort.open(portName);
	while( !threadShouldExit()) {
		wait(1); //prevent 100% cpu use here; also assume that we won't get messages at > 1000Hz
		if (yarpPort.getPendingReads()) {
			//read port here
			yarp::os::Bottle* bot = yarpPort.read();
			lock.enter();
			if (textOutput.length() >= 512)
				textOutput.clear(); //clear if too big.
			textOutput+= bot->toString().c_str() + String("\n");
			lock.exit();
			DBG("textOutput size = " + String(textOutput.length()));
			sendChangeMessage();
		}
	}
	yarpPort.close();
	DBG("yarp read thread exiting...");
}

