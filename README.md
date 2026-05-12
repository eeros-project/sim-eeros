# sim-eeros
The [EEROS Robotics Framework](https://github.com/eeros-project/eeros-framework) uses various [hardware libraries](http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries) to access the underlying hardware. The simulator can be used to test EEROS applications without the need of external hardware. EEROS includes some examples which require the simulator.

## Documentation
- About the simulator: https://wiki.eeros.org/eeros_architecture/hal/hardware_libraries_sim
- About the wrapper library: http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries#simulator
- How to install: http://wiki.eeros.org/getting_started/install_wrapper#simulator
- Extending the simulator: http://wiki.eeros.org/for_developers/simulator
  
## Getting Started
Check the following examples for the use of the wrapper library.
- [Use on the Host](https://wiki.eeros.org/getting_started/install/use_on_host)

The EEROS [Hardware Abstraction Layer](http://wiki.eeros.org/eeros_architecture/hal/start) needs a [configuration file](http://wiki.eeros.org/eeros_architecture/hal/configuration_file) which describes the hardware. A sample hardware configuration file for this wrapper library can be found at
- [https://gitlab.ost.ch/tech/inf/public/cb20/-/blob/master/Software/cb20test/HwConfigCb20.json](https://github.com/eeros-project/eeros-framework/blob/master/examples/hal/HalTest1Config.json)

## How to contribute
The EEROS team would love to accept your contributions! The development on the EEROS Framework is done with the work flow “**develop with a fork**”. So please fork the repository, develop and test your code changes. For code quality, please follow the guidelines put together [here](http://wiki.eeros.org/for_developers/start). In general, the code should adheres to the existing style in the project. Once the changes are ready, a pull request is submitted. Each logical change should be submitted separately to ensure that the history will be understandable.
