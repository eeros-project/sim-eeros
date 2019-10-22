# sim-eeros
Hardware simulator for [EEROS Robotics Framework](https://github.com/eeros-project/eeros-framework).
The simulator can be used to test EEROS applications without external hardware. EEROS includes some examples which require the simulator.

## Documentation
- Project Website: (http://www.eeros.org)
- Project Wiki: (http://wiki.eeros.org)
- Hardware Abstraction Layer: (http://wiki.eeros.org/eeros_architecture/hal/start) 
- Using the simulator: http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries#simulator
- Extending the simulator: http://wiki.eeros.org/for_developers/simulator 

## Getting Started

The easiest way to get started using EEROS is described in [Installation and Setup](https://wiki.eeros.org/getting_started/install_and_setup_development_environment) and more specifically in [Use on the Host](https://wiki.eeros.org/getting_started/install_and_setup_development_environment/use_on_host).

The EEROS framework uses various [hardware libraries](http://wiki.eeros.org/eeros_architecture/hal/hardware_libraries) to access the underlying hardware.

The EEROS [Hardware Abstraction Layer](http://wiki.eeros.org/eeros_architecture/hal/start) needs a [configuration file](http://wiki.eeros.org/eeros_architecture/hal/configuration_file) which describes the hardware, or in our case the simulator. A hardware configuration file describing the features in the simulator can be found at (https://github.com/eeros-project/eeros-framework/tree/master/examples/hal). It is called *HalTest1Config.json*.


## How to contribute to sim-eeros

The [EEROS Team](http://eeros.org/eeros-team/) would love to accept your contributions! The development on the EEROS Framework is done with the work flow “**develop with a fork**”. So please fork the repository, develop and test your code changes. For code quality, please follow the guidelines put together [here](http://wiki.eeros.org/for_developers/start). In general, the code should adheres to the existing style in the project. Once the changes are ready, a pull request is submitted. Each logical change should be submitted separately to ensure that the history will be understandable.
