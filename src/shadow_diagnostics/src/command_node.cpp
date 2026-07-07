#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <functional>

class CommandNode: public rclcpp::Node
{
private:

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        bool publish_running_ = true;

        void command_timer_callback(){
            std_msgs::msg::String msg;
            if (publish_running_){
                msg.data = "RUNNING";
            }
            else{
                msg.data = "STOP";
            }
            RCLCPP_INFO(
                this->get_logger(),
                "Publishing command: %s",
                msg.data.c_str()
            );

            publisher_->publish(msg);
            publish_running_ = !publish_running_;
        }

public:        
        CommandNode() : Node("command_node"){
            publisher_  = this->create_publisher<std_msgs::msg::String>("/robot_command", 10);
            
            timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&CommandNode::command_timer_callback, this)
        );
        }

       

};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CommandNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}