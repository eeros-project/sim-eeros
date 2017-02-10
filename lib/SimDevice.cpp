#include <SimDevice.hpp>
#include <eeros/core/EEROSException.hpp>
#include <unistd.h>

using namespace sim;

std::map<std::string, SimDevice *> SimDevice::devices;

#define NOF_SIM_CHANNELS 5

// device will select function 

SimDevice::SimDevice(std::string simId) {
	this->simId = simId;
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		throw new eeros::EEROSException("device already open, claim already opened device via getDevice()");
	}
	
	// creating all Simulation Devices and Channels
	
	// reflect digital Outputs
	for(int i = 0; i < NOF_SIM_CHANNELS; i++){
		reflectSimDigOut_DigOutputs.push_back(new SimChannel<bool>(0, i));
		reflectSimDigOut_DigInputs.push_back(new SimChannel<bool>(1, i));
		
		reflectSimDigIn_DigInputs.push_back(new SimChannel<bool>(2, i));
		reflectSimDigIn_DigOutputs.push_back(new SimChannel<bool>(3, i));
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
	if(simId == "reflect"){
		if(reflectSimDigOut_DigOutputs[0]->getSubDevice() == subdeviceNumber){
			for(int i = 0; i < reflectSimDigOut_DigOutputs.size(); i++){
				if(reflectSimDigOut_DigOutputs[i]->getChannel() == channel){
					return reflectSimDigOut_DigOutputs[i];
				}
			}
		}
		else if(reflectSimDigOut_DigInputs[0]->getSubDevice() == subdeviceNumber){
			for(int i = 0; i < reflectSimDigOut_DigInputs.size(); i++){
				if(reflectSimDigOut_DigInputs[i]->getChannel() == channel){
					return reflectSimDigOut_DigInputs[i];
				}
			}
		}
	}
	else{
		throw eeros::EEROSException("getChannel failed: no such device");
	}
}

void SimDevice::run() {
	while(true){
		// simulate digital Output: reflect values to reflectSimDigOut_DigInputs
		for(int i = 0; i < reflectSimDigOut_DigOutputs.size(); i++){
			reflectSimDigOut_DigInputs[i]->setValue(reflectSimDigOut_DigOutputs[i]->getValue());
		}
		// simulate digital Input: reflect values from reflectSimDigIn_DigOutputs
		for(int i = 0; i < reflectSimDigIn_DigInputs.size(); i++){
			reflectSimDigIn_DigInputs[i]->setValue(reflectSimDigIn_DigOutputs[i]->getValue());
		}
		usleep(1000);
	}
}

