#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("msg_cnt_pub") {
        cnt_ = 0;
        publisher_ = rclcpp::create_publisher<std_msgs::msg::UInt8>(this, "/counter", rclcpp::SensorDataQoS());

        // create a callback group if you want to create service as well, to prevent deadlocks.
        timerCbGroup_ = nullptr;
        timer_ = rclcpp::create_wall_timer(1000ms,
                                           [this]() -> void { timerCallback(); },
                                           timerCbGroup_,
                                           this->get_node_base_interface().get(),
                                           this->get_node_timers_interface().get());

        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void timerCallback() {
        RCLCPP_INFO(get_logger(), "Timer callback fired, publishing: %ld!", cnt_);

        std_msgs::msg::UInt8 msg;
        msg.data = cnt_++;
        publisher_->publish(msg);
    }

private:
    long int cnt_;

    rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr publisher_;
    rclcpp::CallbackGroup::SharedPtr timerCbGroup_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
