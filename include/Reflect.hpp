#ifndef SIM_EEROS_REFLECT_HPP_
#define SIM_EEROS_REFLECT_HPP_

#include <vector>

#include <SimBehaviour.hpp>
#include <SimChannel.hpp>
#include <eeros/core/EEROSException.hpp>

namespace sim{

	template <typename T>
	class Reflect : sim::SimBehaviour<T> {
		public:
			Reflect(int nofSimChannels, std::initializer_list<int> subDeviceNumber) : subDevNumbers(subDeviceNumber){
				if(subDeviceNumber.size() != 2){
					throw eeros::EEROSException("number of SubDeviceNumbers is not 2!");
				}
				// create channels
				for(int i = 0; i < nofSimChannels; i++){
					in.push_back(new SimChannel<T>(subDevNumbers[0], i));
					out.push_back(new SimChannel<T>(subDevNumbers[1], i));
				}
			}
			~Reflect() {
				in.clear();
				out.clear();
			}
			virtual void run(){
				// reflect
				for(int i = 0; i < in.size(); i++){
					out[i]->setValue(in[i]->getValue());
				}
			}
			
			virtual sim::SimChannel<T> * getInChannel(int channel){
				for(int i = 0; i < in.size(); i++){
					if(in[i]->getChannel() == channel){
						return in[i];
					}
				}
				throw eeros::EEROSException("In channel not found");
			}
			
			virtual sim::SimChannel<T> * getOutChannel(int channel){
				for(int i = 0; i < out.size(); i++){
					if(out[i]->getChannel() == channel){
						return out[i];
					}
				}
				throw eeros::EEROSException("Out channel not found");
			}
			
		private:
			// simulation: reflect in to out
			std::vector<sim::SimChannel<T> *> out;
			std::vector<sim::SimChannel<T> *> in;
			
			std::vector<int> subDevNumbers;
  
	};
};

#endif /* SIM_EEROS_REFLECT_HPP_ */