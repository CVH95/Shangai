# AI3 Final Project

This project belongs to the course of **Adaptive Embodied Locomotion Control Systems**, which is part of the 3rd semester of MSc in Robot Systems at University of Southern Denmark.

For a more detailed report on the project, go to the repo's [Wiki](https://github.com/CVH95/Shangai/wiki).

## 1. Project Description.

### 1.1. Contents.

The repo contains several directories and files:
 
 - **controller:** Implementation of the controller for the real LocoKit robot in C++. Uses the LocoKitInterface API for C++.
 - **Neuron:** C++ implementation of a class to define neurons as objects.
 - **PSN:** C++ implementation of a class to define Phase Switching Netwoks (L9 - Modular Neural Control).
 - **RK4:** C++ implementation of a class with mathematical methods to solve ODEs numerically with the Runge-Kutta approximation (L8 - Dynamic Computation and Muscle Model).
 - **simulation:** Interface for simulation of the LocoKit robot controller using LPZROBOTS C++ framework. 
 - **SO2:** C++ implementation of a class that defines an SO2 Central Pattern Generator network (L8 - Dynamic Computation and Muscle Model).
 - **TransferFuntion:** C++ implementation of a class with mathematical transfer functions commonly used in artificial neurons.
 - **VRN:** C++ implementation of a class to decine Velocity Reduction Networks (L9 - Modular Neural Control). 
 - **tests:** Contains tests for the above projects.


## Authors

Carlos Viescas Huerta.

cavie17@student.sdu.dk

## References

 - [LocoKit](https://locokit.sdu.dk/) robot.
 - LocoKit [C API](https://locokit.sdu.dk/static/doxydir/html/locoapi_8h.html).
 - LocoKit [Python API](https://locokit.sdu.dk/static/Python/locox.html).
 - LPZROBOTS [C++ framework](http://robot.informatik.uni-leipzig.de/software/).
 - LPZROBOTS [git repository](https://github.com/pmanoonpong/lpzrobots).
 - Gorobots-edu [git repository](https://github.com/pmanoonpong/gorobots_edu).