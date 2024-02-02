#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("msg_cnt_sub") {
        subscriber_ = rclcpp::create_subscription<std_msgs::msg::UInt8>(*this,
                                                                        "/counter",
                                                                        rclcpp::SensorDataQoS(),
                                                                        std::bind(&MyNode::onSubscription, this, _1));
        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void onSubscription(const std_msgs::msg::UInt8::SharedPtr cnt) {
        RCLCPP_INFO(get_logger(), "Counter: %d", cnt->data);
    }

private:
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr subscriber_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
