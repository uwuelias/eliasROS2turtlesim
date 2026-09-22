# ROS2 Turtle Sim Design Doc

## Introduction

The purpose of this document is to provide a comprehensive overview of the software design for the ROS2 Turtle Sim. This includes the goal, controls, architecture, file structure, and implementation. 

## Goal

The goal is to create a C++ ROS2 program that allows a user to control a TurtleSim turtle from the command line.

## Controls

- W -- move forward
- A -- rotate left
- S -- move backward
- D -- rotate right
- Q -- quit

## Architecture

Keyboard Input --> Turtle Controller --> Protobuf TurtleCommand --> ROS2 Twist Message --> TurtleSim

The project will use a single ROS2 node. The node will read keyboard input, create a protobuf command containing the desired velocities, convert that command into ROS2 Twist message, and BOOM, turtle move.

For the controls, we will be using termios so keypresses can be read immediately without pressing enter. Each keypresses represent one movement. holding down the key = pressing the key

The Protobuf message will contain:
- Linear velocity 
- Angular velocity

## File Structure
```
eliasROS2turtlesim
├── DESIGN.md
├── include
│   └── turtle_controller.hpp
├── proto
│   └── turtle_command.proto
├── README.md
├── run.sh
└── src
    ├── CMakeLists.txt
    ├── package.xml
    └── turtle_controller.cpp
```

## Implementation

The project will be implemented in C++ using:
- ROS2
- TurtleSim
- rclcpp
- proto2ros

## Run
```Bash
./run.sh
```