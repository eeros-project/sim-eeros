#ifndef SIM_EEROS_DEVICE_HPP_
#define SIM_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <thread>
#include <SimChannel.hpp>
#include <Reflect.hpp>

namespace sim {
	enum SubDeviceNumber{
			REFLECT_OUT_DIGOUT = 0,
			REFLECT_OUT_DIGIN = 1,
			
			REFLECT_IN_DIGIN = 2,
			REFLECT_IN_DIGOUT = 3,
			
			REFLECT_OUT_AOUT = 4,
			REFLECT_OUT_AIN = 5,
			
			REFLECT_IN_AIN = 6,
			REFLECT_IN_AOUT = 7
	};

	class SimDevice {
	public:
		virtual ~SimDevice();
		virtual std::shared_ptr<SimChannel<bool>> getLogicChannel(int subDeviceNumber, int channel);
		virtual std::shared_ptr<SimChannel<uint64_t>> getRealChannel(int subDeviceNumber, int channel);
		static SimDevice* getDevice(std::string simId);

        private:
		SimDevice(std::string simId);
		virtual void run();
		
		std::string simId;
		
		// logic channels
		sim::Reflect<bool> reflectDigOut;
		sim::Reflect<bool> reflectDigIn;
		
		// real channels: max 32 bit resolution
		sim::Reflect<uint64_t> reflectAnalogOut;
		sim::Reflect<uint64_t> reflectAnalogIn;
		
		static std::map<std::string, sim::SimDevice *> devices;
		std::thread* t;
	};
};

#endif /* SIM_EEROS_DEVICE_HPP_ */ 
