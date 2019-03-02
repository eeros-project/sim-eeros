#ifndef SIM_EEROS_DEVICE_HPP_
#define SIM_EEROS_DEVICE_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <thread>
#include "SimChannel.hpp"
#include "Reflect.hpp"

namespace sim {
	enum SubDeviceNumber{
			REFLECT_DOUT = 0,
			REFLECT_DIN = 1,
			
			REFLECT_AOUT = 2,
			REFLECT_AIN = 3
	};
	
	const std::vector<std::string> simFeatures = {
		"reflect"
	};

	class SimDevice {
	public:
		virtual ~SimDevice();
		virtual std::shared_ptr<SimChannel<bool>> getLogicChannel(int subDeviceNumber, int channel);
		virtual std::shared_ptr<SimChannel<double>> getRealChannel(int subDeviceNumber, int channel);
		static SimDevice* getDevice(std::string simId);

        private:
		SimDevice(std::string simId, int nofSimChannels, std::initializer_list<int> subDevNumDig, std::initializer_list<int> subDevNumAn);
		virtual void run();
		
		std::string simId;
		sim::Reflect<bool> dig;	// logic channels
		sim::Reflect<double> an;	// real channels		
		std::vector<sim::SimBehaviour<double> *> scalableSimBlocks;
		std::vector<sim::SimBehaviour<bool> *> logicSimBlocks;
		
		static std::map<std::string, sim::SimDevice *> devices;
		std::thread* t;
	};
};

#endif /* SIM_EEROS_DEVICE_HPP_ */ 
