#include <functional>
#include <future>
#include <map>
#include <memory>
#include <string>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int32.hpp"

#include "irobot_create_msgs/action/dock.hpp"
#include "irobot_create_msgs/action/undock.hpp"

#include "isl2_create3_joy_control/dock_handler.hpp"
#include "isl2_create3_joy_control/undock_handler.hpp"
using std::placeholders::_1;

class JoyController : public rclcpp::Node {
public:
  using Dock = irobot_create_msgs::action::Dock;
  using Undock = irobot_create_msgs::action::Undock;

  JoyController() : Node("joy_controller") {
    dock_handler_ = DockHandler(this);
    undock_handler_ = UndockHandler(this);
    joy_subcription_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10, std::bind(&JoyController::joy_callback, this, _1)
    );

    dock_button = 2;
    undock_button = 3;

    RCLCPP_INFO(this->get_logger(), "JoyController initialized.");
  }
private:
  void joy_callback(const sensor_msgs::msg::Joy & msg) {

    if(msg.buttons[dock_button] == 1 && msg.buttons[undock_button] == 0 && dock_mutex.try_lock()) {
      dock_handler_.send_goal();
      dock_mutex.unlock();
    }

    if(msg.buttons[dock_button] == 0 && msg.buttons[undock_button] == 1 && dock_mutex.try_lock()) {
      undock_handler_.send_goal();
      dock_mutex.unlock();
    }
  }

  std::mutex dock_mutex;
  DockHandler dock_handler_;
  UndockHandler undock_handler_;
  int dock_button;
  int undock_button;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subcription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JoyController>());
  rclcpp::shutdown();
  return 0;
}

