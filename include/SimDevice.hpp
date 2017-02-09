#ifndef SIM_EEROS_DEVICE_HPP_
#define SIM_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <vector>
#include <thread>
#include <SimChannel.hpp>

namespace sim {

	class SimDevice {
	public:
		SimDevice(std::string simId);
		virtual ~SimDevice();
		virtual SimChannel<bool>* getChannel(int subdeviceNumber, int channel);
		static SimDevice* getDevice(std::string simId);

        private:
		virtual void run();
		
		static std::map<std::string, sim::SimDevice *> devices;
		std::string simId;
		
		std::vector<sim::SimChannel<bool> *> digOutputs;
		std::vector<sim::SimChannel<bool> *> digInputs;
		
		std::thread* t;
	};
};

#endif /* SIM_EEROS_DEVICE_HPP_ */ 
