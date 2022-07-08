//“/goal_pose geometry_msgs::msg::PoseStamped”
//ros2 topic pub /goal_pose geometry_msgs/PoseStamped "{header: {stamp: {sec: 0}, frame_id: 'map'}, pose: {position: {x: 1.0, y: 1.0, z: 0.0}, orientation: {w: 1.0}}}"


#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int16.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include <vector>
#include "rclcpp/clock.hpp"
#include "std_msgs/msg/header.hpp"

using std::placeholders::_1;

class Ps2_SubscribeandPublish : public rclcpp::Node{
  public:
    Ps2_SubscribeandPublish()
    : Node("Ps2_SubscribeandPublish")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int16>(
      "service", 10, std::bind(&Ps2_SubscribeandPublish::sub_callback, this, _1));
      
      //这里要改成发布目标点的位置信息就行
      publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", 10);
      //timer_ = this->create_wall_timer(2500ms, std::bind(&Ps2_Publisher::timer_callback, this));
      //publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose"，50);
    }
  private:
    void sub_callback(const std_msgs::msg::Int16::SharedPtr msg) {
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
      std::cout<<i<<std::endl;
      if (i<1)
      {
          auto message = geometry_msgs::msg::PoseStamped();
          message.header = std_msgs::msg::Header();
          message.header.frame_id = "pose_frame";
          message.header.stamp = rclcpp::Clock().now();

          message.pose.position.x = 0;
          message.pose.position.y = 0;
          message.pose.position.z = 0;

          message.pose.orientation.x = 0;
          message.pose.orientation.y = 0;
          message.pose.orientation.z = 0;
          message.pose.orientation.w = 1;

          RCLCPP_INFO(this->get_logger(), "pub goal pose");
          publisher_->publish(message);
          i=i+1;
          //ROS_INFO("we publish the robot's position and orientaion");
        //RCLCPP_INFO(this->get_logger(),"the position(x,y,z) is %f , %f, %f", message.pose.position.x, message.pose.position.y, message.pose.position.z);
        //ROS_INFO("the orientation(x,y,z,w) is %f , %f, %f, %f", message.pose.orientation.x, message.pose.orientation.y, message.pose.orientation.z, message.pose.orientation.w);
        //ROS_INFO("the time we get the pose is %f",  msg.header.stamp.sec + 1e-9*msg.header.stamp.nsec);

      	
      	//pub.publisher_;

      }
    }
        rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscription_;
    	//rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
        int i=0;
    };

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ps2_SubscribeandPublish>());
  rclcpp::shutdown();
  return 0;
}
