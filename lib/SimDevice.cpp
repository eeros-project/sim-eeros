#include <SimDevice.hpp>
#include <eeros/core/EEROSException.hpp>
#include <unistd.h>
#include <iostream>

using namespace sim;

std::map<std::string, SimDevice *> SimDevice::devices;

#define NOF_SIM_CHANNELS 10

// device will select function 

SimDevice::SimDevice(std::string simId) : 
		      reflectDigOut(NOF_SIM_CHANNELS, {REFLECT_OUT_DIGOUT, REFLECT_OUT_DIGIN}), 
		      reflectDigIn(NOF_SIM_CHANNELS, {REFLECT_IN_DIGIN, REFLECT_IN_DIGOUT}),
		      reflectAnalogOut(NOF_SIM_CHANNELS, {REFLECT_OUT_AOUT, REFLECT_OUT_AIN}),
		      reflectAnalogIn(NOF_SIM_CHANNELS, {REFLECT_IN_AIN, REFLECT_IN_AOUT}) {
	this->simId = simId;
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		throw new eeros::EEROSException("device already open, claim already opened device via getDevice()"); // should not occur!
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
		if(simId == "reflect"){
			return new SimDevice(simId);
		}
		throw eeros::EEROSException(simId + " not supported.");
	}
}

std::shared_ptr<SimChannel<bool>> SimDevice::getLogicChannel(int subDeviceNumber, int channel) {
	if(simId == "reflect"){
		// digital output simulation block
		
		switch(subDeviceNumber){
			// simulate digital Out
			case REFLECT_OUT_DIGOUT:{
				return reflectDigOut.getInChannel(channel);
				break;		// not reached
			}
			case REFLECT_OUT_DIGIN:{
				return reflectDigOut.getOutChannel(channel);
				break;		// not reached
			}
			// simulate digital In
			case REFLECT_IN_DIGIN:{
				return reflectDigIn.getOutChannel(channel);
				break;
			}
			case REFLECT_IN_DIGOUT:{
				return reflectDigIn.getInChannel(channel);
				break;
			}
		}
	}
	else{
		throw eeros::EEROSException("getChannel failed: no such device");
	}
}

std::shared_ptr<SimChannel<uint64_t>> SimDevice::getRealChannel(int subDeviceNumber, int channel) {
	if(simId == "reflect"){
		// digital output simulation block
		std::cout << "subD: " << subDeviceNumber << "\tchan: " << channel << std::endl;
		switch(subDeviceNumber){
			// simulate analog Out
			case REFLECT_OUT_AOUT:{
				std::cout << "out_aout " << std::endl;
				return reflectAnalogOut.getInChannel(channel);
				break;		// not reached
			}
			case REFLECT_OUT_AIN:{
				std::cout << "out_ain " << std::endl;
				return reflectAnalogOut.getOutChannel(channel);
				break;		// not reached
			}
			// simulate analog In
			case REFLECT_IN_AIN:{
				return reflectAnalogIn.getOutChannel(channel);
				break;
			}
			case REFLECT_IN_AOUT:{
				return reflectAnalogIn.getInChannel(channel);
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
		reflectAnalogOut.run();
		reflectAnalogIn.run();
		
		usleep(100000);
	}
}

