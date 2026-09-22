cmake_minimum_required(VERSION 3.8)

project(eliasROS2turtlesim)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(turtle_controller
    turtle_controller.cpp
)

ament_target_dependencies(
    turtle_controller
    rclcpp
    geometry_msgs
)

target_include_directories(
    turtle_controller
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(
    TARGETS turtle_controller
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()