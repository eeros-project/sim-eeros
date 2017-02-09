#ifndef SIM_EEROS_CHANNEL_HPP_
#define SIM_EEROS_CHANNEL_HPP_

#include <map>

namespace sim {
	template <typename T>
	class SimChannel {
		public:
			SimChannel(int subDevice, int channel);
			virtual T getValue() { return value; };
			virtual void setValue(T val) { value = val; };
			
			virtual int getSubDevice() { return subDevice; };
			virtual int getChannel() { return channel; };
			
		private:
			int subDevice;
			int channel;
			T value;
	};
};

#endif /* #ifndef SIM_EEROS_CHANNEL_HPP_ */