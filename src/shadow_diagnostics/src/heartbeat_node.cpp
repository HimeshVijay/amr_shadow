#include <rclcpp/rclcpp.hpp>
#include "shadow_interfaces/msg/robot_status.hpp"
#include <chrono>
#include <memory>
#include <functional>
#include <std_msgs/msg/string.hpp>


class HeartbeatNode: public rclcpp::Node
{
private:
        rclcpp::Publisher<shadow_interfaces::msg::RobotStatus>::SharedPtr status_publisher_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;
        rclcpp::TimerBase::SharedPtr timer_;
        // std::string current_state_ = "running";

        shadow_interfaces::msg::RobotStatus current_status_;
        // float current_battery_percentage = 100.0;
        // bool current_emergency_stop = false;
        // uint16_t current_error_code = 0;
        // float current_system_temperature = 35.0;

        void heartbeat_timer_callback(){
          //  RCLCPP_INFO(this->get_logger(), "Callback Executed");
            //shadow_interfaces::msg::RobotStatus msg;
            // msg.battery_percentage = current_battery_percentage;    = we will use a single
            // msg.state = current_state_;                               status publisher instead of creating five. 
            // msg.emergency_stop = current_emergency_stop;                
            // msg.error_code = current_error_code;                        
            // msg.system_temperature = current_system_temperature;
            // status_publisher_ -> publish(msg);
            status_publisher_ ->publish(current_status_);
        }

        void robot_command_callback(const std_msgs::msg::String::SharedPtr msg){
            current_status_.state = msg->data;

            RCLCPP_INFO(
                this->get_logger(),
                "received command: %s",
                current_status_.state.c_str()
            );
        }

public:
        HeartbeatNode(): Node("heartbeat_node"){

            current_status_.state = "RUNNING";
            current_status_.battery_percentage = 100.0f;
            current_status_.emergency_stop = false;
            current_status_.error_code = 0;
            current_status_.system_temperature = 35.0f;

            //RCLCPP_INFO(this->get_logger(), "Heartbeat Node Started");
            status_publisher_ = this-> create_publisher<shadow_interfaces::msg::RobotStatus>("/robot_status",10);
            command_subscriber_= this-> create_subscription<std_msgs::msg::String>("/robot_command",
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