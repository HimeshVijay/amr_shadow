#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <memory>
#include <functional>



class HeartbeatNode: public rclcpp::Node
{
private:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::string current_state_ = "running";

        void heartbeat_timer_callback(){
          //  RCLCPP_INFO(this->get_logger(), "Callback Executed");
            std_msgs::msg::String msg;
            msg.data = current_state_;
            publisher_ -> publish(msg);
        }

        void robot_command_callback(const std_msgs::msg::String::SharedPtr msg){
            current_state_ = msg->data;

            RCLCPP_INFO(
                this->get_logger(),
                "received command: %s",
                current_state_.c_str()
            );
        }

public:
        HeartbeatNode(): Node("heartbeat_node"){
            //RCLCPP_INFO(this->get_logger(), "Heartbeat Node Started");
            publisher_ = this-> create_publisher<std_msgs::msg::String>("/robot_status",10);
            subscriber_= this-> create_subscription<std_msgs::msg::String>("/robot_command",
            10,
            std::bind(&HeartbeatNode::robot_command_callback, this, std::placeholders::_1)
            );
            timer_ = this-> create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&HeartbeatNode::heartbeat_timer_callback, this)
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