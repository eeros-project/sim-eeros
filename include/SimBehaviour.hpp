#ifndef SIM_EEROS_BEHAVIOUR_HPP_
#define SIM_EEROS_BEHAVIOUR_HPP_

#include <SimChannel.hpp>

namespace sim{
	template <typename T>
	class SimBehaviour {
		public:
			virtual ~SimBehaviour() {};
			virtual void run() = 0;
			virtual sim::SimChannel<T>* getInChannel(int channel) = 0;
			virtual sim::SimChannel<T>* getOutChannel(int channel) = 0;
	};
};

#endif /* SIM_EEROS_BEHAVIOUR_HPP_ */