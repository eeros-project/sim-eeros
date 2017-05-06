# sim-eeros
Hardware Simulator for https://github.com/eeros-project

## Documentation
- Using the simulator: (http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries#simulator) 
- Extending the simulator: (http://wiki.eeros.org/for_developers/simulator) 

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
for a complete example visit https://github.com/akalberer/eeros-framework/tree/hal/examples/sim 
or soon on https://github.com/eeros-project/eeros-framework

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
