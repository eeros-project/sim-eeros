#include <SimAnalogIn.hpp>
#include <iostream>

using namespace sim;

AnalogIn::AnalogIn(std::string id,
					 void* libHandle,
					 std::string device,
					 uint32_t subDeviceNumber,
					 uint32_t channel,
					 double scale,
					 double offset,
					 double rangeMin,
					 double rangeMax,
					 std::string unit
		  ) : ScalableInput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit) {
	SimDevice *dev = SimDevice::getDevice(device);
	this->chan = dev->getRealChannel(subDeviceNumber, channel);
}

double AnalogIn::get() {
	double inVal = (chan->getValue() - offset) / scale;
	if(inVal > maxIn) inVal = maxIn;
	if(inVal < minIn) inVal = minIn;
	
	return inVal;
}

extern "C"{
	eeros::hal::ScalableInput<double> *createAnalogIn(std::string id, 
							void* libHandle, 
							std::string device, 
							uint32_t subDeviceNumber, 
							uint32_t channel, 
							double scale, 
							double offset, 
							double rangeMin, 
							double rangeMax, 
							std::string unit){
		return new sim::AnalogIn(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
}
