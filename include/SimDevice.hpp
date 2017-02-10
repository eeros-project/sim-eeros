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
		
		// simulate digital Output: will reflect value to reflectOutDigInputs
		std::vector<sim::SimChannel<bool> *> reflectSimDigOut_DigOutputs;
		std::vector<sim::SimChannel<bool> *> reflectSimDigOut_DigInputs;
		
		// simulate digital Input: will reflect value from reflectSimDigIn_DigInputs
		std::vector<sim::SimChannel<bool> *> reflectSimDigIn_DigInputs;
		std::vector<sim::SimChannel<bool> *> reflectSimDigIn_DigOutputs;
		
		std::thread* t;
	};
};

#endif /* SIM_EEROS_DEVICE_HPP_ */ 
