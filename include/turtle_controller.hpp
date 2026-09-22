#ifndef TURTLE_CONTROLLER_HPP
#define TURTLE_CONTROLLER_HPP

#include <termios.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TurtleController : public rclcpp::Node
{
public:
    TurtleController();
    ~TurtleController();

private:
    void readKeyboard();
    void publishMovement(double linear, double angular);
    void stopTurtle();

    void setupTerminal();
    void restoreTerminal();

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    struct termios original_terminal_;
};

#endif