#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <memory>
#include <functional>



class HeartbeatNode: public rclcpp::Node
{
private:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;

        void heartbeat_publish(){
          //  RCLCPP_INFO(this->get_logger(), "Callback Executed");
            std_msgs::msg::String msg;
            msg.data = "Node is healthy";
            publisher_ -> publish(msg);
        };

public:
        HeartbeatNode(): Node("heartbeat_node"){
            //RCLCPP_INFO(this->get_logger(), "Heartbeat Node Started");
            publisher_ = this-> create_publisher<std_msgs::msg::String>("/robot_status",10);
            timer_ = this-> create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&HeartbeatNode::heartbeat_publish, this)
            );
        }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HeartbeatNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}