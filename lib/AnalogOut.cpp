#include <SimAnalogOut.hpp>
#include <iostream>

using namespace sim;

AnalogOut::AnalogOut(std::string id,
					 void* libHandle,
					 std::string device,
					 uint32_t subDeviceNumber,
					 uint32_t channel,
					 double scale,
					 double offset,
					 double rangeMin,
					 double rangeMax,
					 std::string unit
		    ) : ScalableOutput<double>(id, libHandle, scale, offset, rangeMin, rangeMax, unit) {
	SimDevice *dev = SimDevice::getDevice(device);
	
	std::cout << "outC s:" << subDeviceNumber << "\tc; " << channel << std::endl;
	this->chan = dev->getRealChannel(subDeviceNumber, channel);
}

double AnalogOut::get() {
	return (static_cast<int64_t>(chan->getValue()) - offset) / scale;
}

void AnalogOut::set(double voltage) {
	int64_t value = static_cast<int64_t>((voltage - offset)/scale);
	
	if(value > maxOut) value = maxOut;
	if(value < minOut) value = minOut;
	
	chan->setValue(static_cast<uint64_t>(value));
}

extern "C"{
	eeros::hal::ScalableOutput<double> *createAnalogOut(std::string id, void* libHandle, std::string device, uint32_t subDeviceNumber, uint32_t channel, 
							    double scale, double offset, double rangeMin, double rangeMax, std::string unit){
		return new sim::AnalogOut(id, libHandle, device, subDeviceNumber, channel, scale, offset, rangeMin, rangeMax, unit);
	}
}
