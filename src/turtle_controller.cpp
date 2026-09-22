#include "turtle_controller/turtle_controller.hpp"

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std::chrono_literals;

TurtleController::TurtleController()
    : Node("turtle_controller")
{
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
        "/turtle1/cmd_vel",
        10
    );

    setupTerminal();

    // check keyboard every 50 milliseconds.
    timer_ = this->create_wall_timer(
        50ms,
        std::bind(&TurtleController::readKeyboard, this)
    );

    RCLCPP_INFO(
        this->get_logger(),
        "WASD Turtle Controller started."
    );

    RCLCPP_INFO(
        this->get_logger(),
        "W = forward | S = backward | A = left | D = right | Q = quit"
    );
}

TurtleController::~TurtleController()
{
    restoreTerminal();
}

void TurtleController::setupTerminal()
{
    tcgetattr(STDIN_FILENO, &original_terminal_);

    struct termios terminal = original_terminal_;

    // disable canonical mode and echo.
    terminal.c_lflag &= ~(ICANON | ECHO);

    // read one character at a time.
    terminal.c_cc[VMIN] = 0;
    terminal.c_cc[VTIME] = 0;

    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &terminal
    );

    // make stdin non-blocking.
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(
        STDIN_FILENO,
        F_SETFL,
        flags | O_NONBLOCK
    );
}

void TurtleController::restoreTerminal()
{
    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &original_terminal_
    );
}

void TurtleController::readKeyboard()
{
    char key;

    if (read(STDIN_FILENO, &key, 1) <= 0) {
        return;
    }

    switch (key)
    {
        case 'w':
        case 'W':
            publishMovement(1.0, 0.0);
            break;

        case 's':
        case 'S':
            publishMovement(-1.0, 0.0);
            break;

        case 'a':
        case 'A':
            publishMovement(0.0, 1.0);
            break;

        case 'd':
        case 'D':
            publishMovement(0.0, -1.0);
            break;

        case 'q':
        case 'Q':
            stopTurtle();

            RCLCPP_INFO(
                this->get_logger(),
                "Exiting controller."
            );

            rclcpp::shutdown();
            break;

        default:
            break;
    }
}

void TurtleController::publishMovement(
    double linear,
    double angular)
{
    geometry_msgs::msg::Twist message;

    message.linear.x = linear;
    message.angular.z = angular;

    publisher_->publish(message);

    // stop after each individual command.
    stopTurtle();
}

void TurtleController::stopTurtle()
{
    geometry_msgs::msg::Twist message;

    message.linear.x = 0.0;
    message.angular.z = 0.0;

    publisher_->publish(message);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto controller =
        std::make_shared<TurtleController>();

    rclcpp::spin(controller);

    rclcpp::shutdown();

    return 0;
}