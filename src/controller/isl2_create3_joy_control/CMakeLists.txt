cmake_minimum_required(VERSION 3.8)
project(isl2_create3_joy_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(irobot_create_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include ${rclcpp_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED
  src/dock_handler.cpp
  src/undock_handler.cpp
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rclcpp_action
  rclcpp_components
  sensor_msgs
  std_msgs
  irobot_create_msgs
)

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)

add_executable(joy_controller src/joy_controller.cpp)
target_link_libraries(joy_controller ${PROJECT_NAME})
ament_target_dependencies(joy_controller
  rclcpp
  rclcpp_action
  rclcpp_components
  sensor_msgs
  std_msgs
  irobot_create_msgs
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(TARGETS
  joy_controller
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
