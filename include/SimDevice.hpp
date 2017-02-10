#ifndef SIM_EEROS_DEVICE_HPP_
#define SIM_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <vector>
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
		virtual SimChannel<bool>* getLogicChannel(int subdeviceNumber, int channel);
		static SimDevice* getDevice(std::string simId);

        private:
		SimDevice(std::string simId);
		virtual void run();
		
		std::string simId;
		
		sim::Reflect<bool> reflectDigOut;
		sim::Reflect<bool> reflectDigIn;
		
		static std::map<std::string, sim::SimDevice *> devices;
		std::thread* t;
	};
};

#endif /* SIM_EEROS_DEVICE_HPP_ */ 
