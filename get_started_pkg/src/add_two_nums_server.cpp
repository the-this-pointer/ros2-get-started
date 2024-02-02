#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "get_started_pkg_interfaces/srv/add_two_nums.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("add_two_nums_serer") {
        addService_ = this->create_service<get_started_pkg_interfaces::srv::AddTwoNums>
                ("addTwoNums",
                 std::bind(&MyNode::addTwoNums, this, _1, _2, _3));

        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void addTwoNums(const std::shared_ptr<rmw_request_id_t> request_header,
                    const std::shared_ptr<get_started_pkg_interfaces::srv::AddTwoNums::Request> request,
                    std::shared_ptr<get_started_pkg_interfaces::srv::AddTwoNums::Response> response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(get_logger(), "add two nums service, a = %ld, b = %ld, result = %ld", request->a, request->b, response->sum);
    }

private:
    rclcpp::Service<get_started_pkg_interfaces::srv::AddTwoNums>::SharedPtr addService_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
