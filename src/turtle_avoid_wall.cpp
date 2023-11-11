#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;

class TestClass : public rclcpp::Node{
    public:
    TestClass() : Node("testclass"){
        sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10, std::bind(&TestClass::topic_callback, this, _1));
        pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/turtle1/cmd_vel", 10);
    };
    private:
    void topic_callback(const turtlesim::msg::Pose & msg) const{
        auto cmd = geometry_msgs::msg::Twist();
        if (msg.x>=10 || msg.y>=10){
            cmd.angular.z = 1.5;
            cmd.linear.x = 0.5;
        }
        else if (msg.x <= 1 || msg.y<=1){
            cmd.angular.z = 1.5;
            cmd.linear.x = 0.5;

        }
        else{
            cmd.linear.x = 2;
        }
        pub_->publish(cmd);
    };
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<TestClass>());
    rclcpp::shutdown();
    return 0;
}