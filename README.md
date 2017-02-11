# sim-eeros
Hardware Simulator for EEROS

## Available devices
* reflect: reflects input from subdevice channel x to output subdevice channel x

## Usage of simulation blocks

#### simulate digital Output
1. connect digital output from eeros-application to subdevice 0 (REFLECT_OUT_DIGOUT) and desired channel x
2. connect digital test input to subdevice 1 (REFLECT_OUT_DIGIN) and channel x
3. you can read state of digital output at your test input channel

#### simulate digital Input
1. connect intput to subdevice 2 (REFLECT_IN_DIGIN) and channel y
2. connect test output to subdevice 3 (REFLECT_IN_DIGOUT) and channel y
3. read state of your input on test output channel

#### example in EEROS config file
example to test digital output "out0" which can be read on test input "inTest0"
```js
{
    "device0": {
		    "library": "libsimeeros.so",
		    "devHandle": "reflect",
		    "subdevice0": {
			          "type": "DigOut",
			          "channel0": {
				              "signalId": "out0"
			          }
		    },
		    "subdevice1": {
			          "type": "DigIn",
			          "channel0": {
				              "signalId": "inTest0"
			          }
		    }
}
```

## Available subdevices
| Function            | Description                     | Subdevice     | available Channels  |
| --------------------|:------------------------------- |:-------------:| :------------------:|
| Digital Output      | Output to test                  |     0         |        0-10         |
|                     | Reflected test input for EEROS  |     1         |        0-10         |
| Digital Input       | Input to test                   |     2         |        0-10         |
|                     | Reflected test output for EEROS |     3         |        0-10         |
| Analog Output       | Output to test                  |     4         |        0-10         |
|                     | Reflected test input for EEROS  |     5         |        0-10         |
| Analog Input        | Input to test                   |     6         |        0-10         |
|                     | Reflected test output for EEROS |     7         |        0-10         |

### for Developers: add new device type to sim-eeros
1. create class derived from SimBehaviour.hpp
1. implement member functions according to your needs
   * constructor: create your simulation channels
   * run() : implement your desired simulation function -> will be called from SimDevice::run()
   * getInChannel(): return shared_ptr to input channel of your device
   * getOutChannel(): return shared_ptr to output channel of your device
1. add channels to SimDevice.hpp (see sim::Reflect<bool> reflectDigOut)
1. call run() of your newly added channels in SimDevice::run(): only with this your device run() is executed
1. add identifier string to available functions
1. add entries to SubDeviceNumber-Enum in SimDevice.hpp with your desired subdevice number for your sim-device
1. add getInChannel() and getOutChannel() of your device type to getLogicChannel() or getRealChannel() in SimDevice.cpp

