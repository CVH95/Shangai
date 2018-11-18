# AI3 Final Project

This project belongs to the course of **Adaptive Embodied Locomotion Control Systems**, which is part of the 3rd semester of MSc in Robot Systems at University of Southern Denmark.

For a more detailed report on the project, go to the repo's [Wiki](https://github.com/CVH95/Shangai/wiki).

## 1. Project Description.

### 1.1. Modular Neural Control

Bio-inspired locomotion control design. MNC corresponds to the CPG-based open-loop control, which retrieves omnidirectional walking with multiple gaits (leg motion pattern). Basic schema of a modular controller:

![MNC blocks](other/MNC.png)

The modular controller has 5 controlling inputs. Basic robot commands in terms of the inputs:

|Action    |i1    |i2    |i3    |i4    |i5    |
|----------|:----:|:----:|:----:|:----:|:----:|
|Forward   |0     |1     |0     |-1    |-1    |
|Backwards |0     |1     |0     |1     |1     |
|Turn right|0     |1     |0     |-1    |1     |
|Turn left |0     |1     |0     |1     |-1    |

## 2. Robot Assembly Design.

## 3. Controller Design and Diagram.

## 4. Implementation.

## 5. Usage.

## 6. Results and Conclusions.

## Authors

Carlos Viescas Huerta.

cavie17@student.sdu.dk

## References

 - [LocoKit](https://locokit.sdu.dk/) robot.
 - LocoKit [C API](https://locokit.sdu.dk/static/doxydir/html/locoapi_8h.html).
 - LocoKit [Python API](https://locokit.sdu.dk/static/Python/locox.html).