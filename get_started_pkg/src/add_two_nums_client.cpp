#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "get_started_pkg_interfaces/srv/add_two_nums.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("add_two_nums_client") {
        cnt_ = 0;

        addNumsClient_ = this->create_client<get_started_pkg_interfaces::srv::AddTwoNums>("addTwoNums");

        // create a callback group if you want to create service as well, to prevent deadlocks.
        timerCbGroup_ = nullptr;
        timer_ = rclcpp::create_wall_timer(15000ms,
                                           [this]() -> void { timerCallback(); },
                                           timerCbGroup_,
                                           this->get_node_base_interface().get(),
                                           this->get_node_timers_interface().get());


        while (!addNumsClient_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service.");
                return;
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
        }

        serviceStarted_ = true;
        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void timerCallback() {
        cnt_++;
        if (!serviceStarted_) {
            RCLCPP_INFO(get_logger(), "Timer callback fired, service not starte. cnt: %ld!", cnt_);
            return;
        }

        auto req = std::make_shared<get_started_pkg_interfaces::srv::AddTwoNums::Request>();
        req->a = cnt_;
        req->b = cnt_ / 2;

        auto result = addNumsClient_->async_send_request(req);
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS)
            RCLCPP_INFO(get_logger(), "Sum: %ld", result.get()->sum);
        else
            RCLCPP_ERROR(get_logger(), "Failed to call service addTwoNums");
    }

private:
    long int cnt_;

    bool serviceStarted_ = false;
    rclcpp::Client<get_started_pkg_interfaces::srv::AddTwoNums>::SharedPtr addNumsClient_;

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
