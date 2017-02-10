#include <SimDevice.hpp>
#include <eeros/core/EEROSException.hpp>
#include <unistd.h>

using namespace sim;

std::map<std::string, SimDevice *> SimDevice::devices;

#define NOF_SIM_CHANNELS 5

// device will select function 

SimDevice::SimDevice(std::string simId) : 
		      reflectDigOut(NOF_SIM_CHANNELS, {REFLECT_OUT_DIGOUT, REFLECT_OUT_DIGIN}), 
		      reflectDigIn(NOF_SIM_CHANNELS, {REFLECT_IN_DIGIN, REFLECT_IN_DIGOUT}) {
	this->simId = simId;
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		throw new eeros::EEROSException("device already open, claim already opened device via getDevice()");
	}
	
	t = new std::thread([this](){ this->run(); });
	
	devices[simId] = this;
}

SimDevice::~SimDevice() {
	auto devIt = devices.find(simId);
	devices.erase(devIt);
	
	delete t;
}

SimDevice* SimDevice::getDevice(std::string simId) {
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		return devIt->second;
	}
	else{
		return new SimDevice(simId);
	}
}

SimChannel<bool>* SimDevice::getLogicChannel(int subDeviceNumber, int channel) {
	if(simId == "reflect"){
		// digital output simulation block
		
		switch(subDeviceNumber){
			// simulate digital Out
			case REFLECT_OUT_DIGOUT:{
				return dynamic_cast<SimChannel<bool>*>(reflectDigOut.getInChannel(channel));
				break;		// not reached
			}
			case REFLECT_OUT_DIGIN:{
				return dynamic_cast<SimChannel<bool>*>(reflectDigOut.getOutChannel(channel));
				break;		// not reached
			}
			// simulate digital In
			case REFLECT_IN_DIGIN:{
				return dynamic_cast<SimChannel<bool>*>(reflectDigIn.getOutChannel(channel));
				break;
			}
			case REFLECT_IN_DIGOUT:{
				return dynamic_cast<SimChannel<bool>*>(reflectDigIn.getInChannel(channel));
				break;
			}
		}
	}
	else{
		throw eeros::EEROSException("getChannel failed: no such device");
	}
}

void SimDevice::run() {
	while(true){
		reflectDigOut.run();
		reflectDigIn.run();
		
		usleep(1000);
	}
}

