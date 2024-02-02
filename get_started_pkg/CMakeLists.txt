cmake_minimum_required(VERSION 3.8)
project(get_started_pkg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set C++ standard to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(get_started_pkg_interfaces REQUIRED)

# publisher
add_executable(msg_cnt_pub src/msg_cnt_pub.cpp)
ament_target_dependencies(msg_cnt_pub rclcpp std_msgs)

install(TARGETS msg_cnt_pub
  DESTINATION lib/${PROJECT_NAME}/
)

# subscriber
add_executable(msg_cnt_sub src/msg_cnt_sub.cpp)
ament_target_dependencies(msg_cnt_sub rclcpp std_msgs)

install(TARGETS msg_cnt_sub
  DESTINATION lib/${PROJECT_NAME}/
)

# add two nums server
add_executable(add_two_nums_server src/add_two_nums_server.cpp)
ament_target_dependencies(add_two_nums_server rclcpp get_started_pkg_interfaces)

install(TARGETS add_two_nums_server
  DESTINATION lib/${PROJECT_NAME}/
)

# add two nums client
add_executable(add_two_nums_client src/add_two_nums_client.cpp)
ament_target_dependencies(add_two_nums_client rclcpp get_started_pkg_interfaces)

install(TARGETS add_two_nums_client
  DESTINATION lib/${PROJECT_NAME}/
)

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
