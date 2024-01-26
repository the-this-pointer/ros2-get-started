#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

class MyNode : public rclcpp::Node
{
public:
   MyNode() : Node("msg_pub") {
       publisher_ = rclcpp::create_publisher<std_msgs::msg::UInt8>(this, "/counter", rclcpp::SensorDataQoS());

      RCLCPP_INFO(get_logger(), "Node started!");
   }
private:
    rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr publisher_;
};

int main(int argc, char **argv)
{
   rclcpp::init(argc, argv);
   auto node = std::make_shared<MyNode>();
   rclcpp::spin(node);
   rclcpp::shutdown();
   return 0;
}
