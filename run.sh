#!/bin/bash

set -e 

PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"

source /opt/ros/humble/setup.bash

mkdir -p "$PROJECT_ROOT/ros2_ws/src"

mkdir -p "$PROJECT_ROOT/ros2_ws/src"

rm -rf "$PROJECT_ROOT/ros2_ws/src/turtle_controller"

mkdir -p "$PROJECT_ROOT/ros2_ws/src/turtle_controller"

cp "$PROJECT_ROOT/src/CMakeLists.txt" \
   "$PROJECT_ROOT/ros2_ws/src/turtle_controller/"

cp "$PROJECT_ROOT/src/package.xml" \
   "$PROJECT_ROOT/ros2_ws/src/turtle_controller/"

cp "$PROJECT_ROOT/src/turtle_controller.cpp" \
   "$PROJECT_ROOT/ros2_ws/src/turtle_controller/"

mkdir -p "$PROJECT_ROOT/ros2_ws/src/turtle_controller/include"

cp "$PROJECT_ROOT/include/turtle_controller.hpp" \
   "$PROJECT_ROOT/ros2_ws/src/turtle_controller/include/"

cd "$PROJECT_ROOT/ros2_ws"

colcon build

source install/setup.bash

ros2 run turtlesim turtlesim_node &
TURTLESIM_PID=$!

sleep 2

ros2 run turtle_controller turtle_controller

kill $TURTLESIM_PID 2>/dev/null || true