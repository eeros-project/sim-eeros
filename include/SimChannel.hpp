#ifndef SIM_EEROS_CHANNEL_HPP_
#define SIM_EEROS_CHANNEL_HPP_

#include <map>

namespace sim {
	template <typename T>
	class SimChannel {
		public:
			SimChannel(int subDevice, int channel) {this->subDevice = subDevice; this->channel = channel;};
			T getValue() { return value; };
			void setValue(T val) { value = val; };
			
			int getSubDevice() { return subDevice; };
			int getChannel() { return channel; };
			
		private:
			int subDevice;
			int channel;
			T value;
	};
};

#endif /* #ifndef SIM_EEROS_CHANNEL_HPP_ */