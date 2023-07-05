#ifndef UNDOCK_HANDLER_HPP
#define UNDOCK_HANDLER_HPP

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int32.hpp"

#include "irobot_create_msgs/action/undock.hpp"

using std::placeholders::_1;


class UndockHandler {
public:
  using Undock = irobot_create_msgs::action::Undock;
  using UndockGoalHandle = rclcpp_action::ClientGoalHandle<Undock>;
  UndockHandler(rclcpp::Node *node);
  UndockHandler() = default;
  void send_goal();
private:
  void response_callback(const UndockGoalHandle::SharedPtr & goal_handle);
  void result_callback(const UndockGoalHandle::WrappedResult & result);

  rclcpp::Node *node_;
  rclcpp_action::Client<Undock>::SharedPtr client_ptr_;
};

#endif