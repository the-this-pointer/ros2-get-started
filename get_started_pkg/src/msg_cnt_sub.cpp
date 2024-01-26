#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node
{
public:
   MyNode() : Node("msg_cnt_sub") {
      RCLCPP_INFO(get_logger(), "Node started!");
   }
private:
    rclcpp::Subscription subscription_;
};

int main(int argc, char **argv)
{
   rclcpp::init(argc, argv);
   auto node = std::make_shared<MyNode>();
   rclcpp::spin(node);
   rclcpp::shutdown();
   return 0;
}
