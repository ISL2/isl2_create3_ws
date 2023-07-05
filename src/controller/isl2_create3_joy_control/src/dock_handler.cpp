#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int32.hpp"

#include "irobot_create_msgs/action/dock.hpp"
#include "isl2_create3_joy_control/dock_handler.hpp"

using std::placeholders::_1;
using std::placeholders::_2;
using Dock = irobot_create_msgs::action::Dock;
using GoalDockHandle = rclcpp_action::ClientGoalHandle<Dock>;


DockHandler::DockHandler(rclcpp::Node *node){
  this->node_ = node;
  this->client_ptr_ = rclcpp_action::create_client<Dock>(
    this->node_,
    "dock"
  );
  RCLCPP_INFO(this->node_->get_logger(), "Dock Handler initialized.");
}

void DockHandler::send_goal() {
  RCLCPP_INFO(this->node_->get_logger(), "DOCK ?");
  if(!this->client_ptr_->wait_for_action_server(std::chrono::milliseconds(5000))){
    RCLCPP_ERROR(this->node_->get_logger(), "Action server not available after waiting");
    return;
  }

  auto goal_msg = Dock::Goal();
  RCLCPP_INFO(this->node_->get_logger(), "Sending goal");

  auto send_goal_options = rclcpp_action::Client<Dock>::SendGoalOptions();
  // send_goal_options.goal_response_callback = std::bind(&DockHandler::response_callback, this, _1);
  send_goal_options.feedback_callback = std::bind(&DockHandler::feedback_callback, this, _1, _2);
  send_goal_options.result_callback = std::bind(&DockHandler::result_callback, this, _1);
  this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
}

// void DockHandler::response_callback(const DockGoalHandle::SharedPtr & goal_handle) {}

void DockHandler::feedback_callback(DockGoalHandle::SharedPtr, const std::shared_ptr<const Dock::Feedback> feedback) {
  if (feedback->sees_dock) {
    RCLCPP_INFO(this->node_->get_logger(), "Attempt docking");
  } else {
    RCLCPP_INFO(this->node_->get_logger(), "Finding dock");
  }
}

void DockHandler::result_callback(const DockGoalHandle::WrappedResult & result) {
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      if (result.result->is_docked) {
        RCLCPP_INFO(this->node_->get_logger(), "Docking successfully");
      } else {
        RCLCPP_INFO(this->node_->get_logger(), "Docking failed successfully");
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