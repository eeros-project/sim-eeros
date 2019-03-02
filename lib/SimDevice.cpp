#include "../include/SimDevice.hpp"
#include <eeros/core/Fault.hpp>
#include <unistd.h>
// device will select function 
#include <iostream>

using namespace sim;

std::map<std::string, SimDevice *> SimDevice::devices;

#define NOF_SIM_CHANNELS 10

SimDevice::SimDevice(std::string simId, int nofSimChannels, std::initializer_list<int> subDevNumDig, std::initializer_list<int> subDevNumAn) :
		      dig(nofSimChannels, subDevNumDig),
		      an(nofSimChannels, subDevNumAn) {
	this->simId = simId;
	
	logicSimBlocks.push_back(&dig);
	scalableSimBlocks.push_back(&an);
	
	auto devIt = devices.find(simId);
	if(devIt != devices.end()){
		throw new eeros::Fault("device already open, claim already opened device via getDevice()"); // should not occur!
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
		for(int i = 0; i < simFeatures.size(); i++){
			if(simFeatures[i] == simId){
				if(simId == "reflect"){
					return new SimDevice(simId, NOF_SIM_CHANNELS, {REFLECT_DOUT, REFLECT_DIN}, {REFLECT_AOUT, REFLECT_AIN});
				}
			}
		}
		throw eeros::Fault("simulation feature '" + simId + "' is not supported.");
	}
}

std::shared_ptr<SimChannel<bool>> SimDevice::getLogicChannel(int subDeviceNumber, int channel) {
	if(simId == "reflect"){
		// digital channel simulation block
		switch(subDeviceNumber){
			case REFLECT_DOUT:{
				return dig.getInChannel(channel);
				break;		// not reached
			}
			case REFLECT_DIN:{
				return dig.getOutChannel(channel);
				break;		// not reached
			}
			default:
				throw eeros::Fault("getChannel failed: no such subdevice");
		}
	}
	else{
		throw eeros::Fault("getLogicChannel failed: no such device");
	}
}

std::shared_ptr<SimChannel<double>> SimDevice::getRealChannel(int subDeviceNumber, int channel) {
	if(simId == "reflect"){
		// analog channel simulation block 	
		switch(subDeviceNumber){
			case REFLECT_AOUT:{
				return an.getInChannel(channel);
				break;		// not reached
			}
			case REFLECT_AIN:{
				return an.getOutChannel(channel);
				break;		// not reached
			}
			default:
				throw eeros::Fault("getRealChannel failed: no such subdevice");
		}
	}
	else{
		throw eeros::Fault("getChannel failed: no such device");
	}
}

void SimDevice::run() {
	while(true){
		
		for(int i = 0; i < logicSimBlocks.size(); i++) {
			logicSimBlocks[i]->run();
		}
		for(int i = 0; i < scalableSimBlocks.size(); i++) {
			scalableSimBlocks[i]->run();
		}
		
		usleep(1000);
	}
}

