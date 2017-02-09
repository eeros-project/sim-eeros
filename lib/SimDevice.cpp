#include <SimDevice.hpp>
#include <eeros/core/EEROSException.hpp>
#include <unistd.h>

using namespace sim;

std::map<std::string, SimDevice *> SimDevice::devices;

#define NOF_SIM_CHANNELS 5

SimDevice::SimDevice(std::string simId) {
	this->simId = simId;
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		throw new eeros::EEROSException("device already open, claim already opened device via getDevice()");
	}
	
	for(int i = 0; i < NOF_SIM_CHANNELS; i++){
		digOutputs.push_back(new SimChannel<bool>(0, i));
		digInputs.push_back(new SimChannel<bool>(1, i));
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

SimChannel<bool>* SimDevice::getChannel(int subdeviceNumber, int channel) {
	if(digOutputs[0]->getSubDevice() == subdeviceNumber){
		for(int i = 0; i < digOutputs.size(); i++){
			return digOutputs[i];
		}
	}
	else if(digInputs[0]->getSubDevice() == subdeviceNumber){
		for(int i = 0; i < digInputs.size(); i++){
			return digInputs[i];
		}
	}
}

void SimDevice::run() {
	while(true){
		for(int i = 0; i < digOutputs.size(); i++){
			digInputs[i]->setValue(digOutputs[i]->getValue());
		}
		usleep(1000);
	}
}

