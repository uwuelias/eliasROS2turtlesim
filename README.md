# eliasROS2turtlesim

A simple WASD keyboard controller for ROS2 TurtleSim, written in C++.

## Overview

This project implements a single ROS2 node, `turtle_controller`, that reads raw keyboard input from the terminal and publishes `geometry_msgs/Twist` messages to `/turtle1/cmd_vel` to drive the turtle in TurtleSim.

```
Keyboard Input --> Turtle Controller --> ROS2 Twist Message --> TurtleSim
```

## Controls

| Key | Action         |
|-----|----------------|
| W   | Move forward   |
| S   | Move backward  |
| A   | Rotate left    |
| D   | Rotate right   |
| Q   | Quit           |

## Project Structure

```
eliasROS2turtlesim
├── Design.md
├── README.md
├── run.sh
├── include
│   └── turtle_controller.hpp
├── proto
│   └── turtle_command.proto
└── src
    ├── CMakeLists.txt
    ├── package.xml
    └── turtle_controller.cpp
```

## Prerequisites

- Ubuntu with ROS2 Humble installed at `/opt/ros/humble`
- `colcon` build tools
- TurtleSim package:
  ```bash
  sudo apt install ros-humble-turtlesim
  ```

## Build & Run

The included script handles setup, build, and launch:

```bash
./run.sh
```

This will:
1. Source your ROS2 Humble environment.
2. Copy the package sources into a local `ros2_ws/` workspace.
3. Build the package with `colcon build`.
4. Launch `turtlesim_node`.
5. Run the `turtle_controller` node so you can drive the turtle with WASD.

### Manual build

If you'd rather build it yourself:

```bash
mkdir -p ros2_ws/src/turtle_controller/include
cp src/CMakeLists.txt src/package.xml src/turtle_controller.cpp ros2_ws/src/turtle_controller/
cp include/turtle_controller.hpp ros2_ws/src/turtle_controller/include/

cd ros2_ws
colcon build
source install/setup.bash

ros2 run turtlesim turtlesim_node &
ros2 run eliasROS2turtlesim turtle_controller
```

> **Note:** The package name registered with ROS2 comes from the `<name>` field in `src/package.xml` (`eliasROS2turtlesim`), not the folder it's copied into. Use that name with `ros2 run`.

## Troubleshooting

- **`Package 'turtle_controller' not found`** — you're running `ros2 run turtle_controller turtle_controller`. Use the actual package name from `package.xml` instead: `ros2 run eliasROS2turtlesim turtle_controller`.
- **Turtle barely moves / doesn't respond to held keys** — each keypress currently publishes a movement command immediately followed by a stop command, so velocity is applied for almost no time. Holding a key should produce continuous movement; if it doesn't, check `publishMovement()` in `turtle_controller.cpp`.
- **No response to any key** — make sure the terminal running `turtle_controller` has focus; keyboard input is read directly from that terminal via `termios`, not from the TurtleSim window.

## Design

See [`Design.md`](./Design.md) for the full design document, including architecture and future plans for a Protobuf-based command layer.

## License

Apache-2.0