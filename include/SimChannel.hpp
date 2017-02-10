#ifndef SIM_EEROS_CHANNEL_HPP_
#define SIM_EEROS_CHANNEL_HPP_

#include <atomic>

namespace sim {
  
	class SimChannelInterface {
		public:
			virtual ~SimChannelInterface() {}
			virtual int getSubDevice() = 0;
			virtual int getChannel() = 0;
	};
	
	template <typename T>
	class SimChannel : public SimChannelInterface {
		public:
			SimChannel(int subDevice, int channel) {this->subDevice = subDevice; this->channel = channel;}
			~SimChannel() {}
			T getValue() { return value.load(); }
			void setValue(T val) { value.store(val); }
			
			int getSubDevice() { return subDevice; }
			int getChannel() { return channel; }
			
		private:
			int subDevice;
			int channel;
			std::atomic<T> value;
	};
};

#endif /* #ifndef SIM_EEROS_CHANNEL_HPP_ */