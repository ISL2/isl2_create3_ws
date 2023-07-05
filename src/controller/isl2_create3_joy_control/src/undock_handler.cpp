#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int32.hpp"

#include "irobot_create_msgs/action/undock.hpp"
#include "isl2_create3_joy_control/undock_handler.hpp"

using std::placeholders::_1;
using Undock = irobot_create_msgs::action::Undock;
using UndockGoalHandle = rclcpp_action::ClientGoalHandle<Undock>;


UndockHandler::UndockHandler(rclcpp::Node *node){
  this->node_ = node;
  this->client_ptr_ = rclcpp_action::create_client<Undock>(
    this->node_,
    "undock"
  );
  RCLCPP_INFO(this->node_->get_logger(), "Undock Handler initialized.");
}

void UndockHandler::send_goal() {
  RCLCPP_INFO(this->node_->get_logger(), "UNDOCK ?");
  if(!this->client_ptr_->wait_for_action_server(std::chrono::milliseconds(5000))){
    RCLCPP_ERROR(node_->get_logger(), "Action server not available after waiting");
    return;
  }

  auto goal_msg = Undock::Goal();
  RCLCPP_INFO(this->node_->get_logger(), "Sending goal");

  auto send_goal_options = rclcpp_action::Client<Undock>::SendGoalOptions();
  // send_goal_options.goal_response_callback = std::bind(&UndockHandler::response_callback, this, _1);
  send_goal_options.result_callback = std::bind(&UndockHandler::result_callback, this, _1);
  this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
}

// void UndockHandler::response_callback(const UndockGoalHandle::SharedPtr & goal_handle) {}

void UndockHandler::result_callback(const UndockGoalHandle::WrappedResult & result) {
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      if (result.result->is_docked) {
        RCLCPP_INFO(this->node_->get_logger(), "Undocking failed successfully");
      } else {
        RCLCPP_INFO(this->node_->get_logger(), "Undocking successfully");
      }
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_ERROR(this->node_->get_logger(), "Docking was aborted");
      return;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_ERROR(this->node_->get_logger(), "Docking was canceled");
      return;
    default:
      RCLCPP_ERROR(this->node_->get_logger(), "Unknown result code");
      return;
  }
}