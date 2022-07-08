#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int16.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

using std::placeholders::_1;
int i=0;

class Vel_subandpub : public rclcpp::Node{
  public:
    Vel_subandpub()
    : Node("Vel_subandpub")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 1, std::bind(&Vel_subandpub::sub_callback, this, _1));
      
      //这里要改成反馈手柄信息
      publisher_ = this->create_publisher<std_msgs::msg::Int16>("topic", 1);
      //timer_ = this->create_wall_timer(2500ms, std::bind(&Ps2_Publisher::timer_callback, this));
      //publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose"，50);
    }

  private:
    void sub_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const
    {


      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
      std::cout<<i<<std::endl;
      if (i<1)
      {
      	auto message = std_msgs::msg::Int16();
      	message.data = 0;
      	RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);

      	publisher_->publish(message);
      	
      	i=i+1;
      }
    }
    //void pub_callback()
    //{
    //  auto message = std_msgs::msg::Int16();
      //message.data = "Hello, world! " + std::to_string(count_++);
    //  message.data = 0;
    //  RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
    //  publisher_->publish(message);
    //}
    //rclcpp::TimerBase::SharedPtr timer_;
    	rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscription_;
    	rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher_;
      //rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
    };

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ps2_SubscribeandPublish>());
  rclcpp::shutdown();
  return 0;
}
