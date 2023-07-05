#ifndef DOCK_HANDLER_HPP
#define DOCK_HANDLER_HPP

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int32.hpp"

#include "irobot_create_msgs/action/dock.hpp"

using std::placeholders::_1;

class DockHandler {
public:
  using Dock = irobot_create_msgs::action::Dock;
  using DockGoalHandle = rclcpp_action::ClientGoalHandle<Dock>;
  DockHandler(rclcpp::Node *node);
  DockHandler() = default;
  void send_goal();
private:
  void response_callback(const DockGoalHandle::SharedPtr & goal_handle);
  void feedback_callback(DockGoalHandle::SharedPtr, const std::shared_ptr<const Dock::Feedback> feedback);
  void result_callback(const DockGoalHandle::WrappedResult & result);

  rclcpp::Node *node_;
  rclcpp_action::Client<Dock>::SharedPtr client_ptr_;
};
#endif