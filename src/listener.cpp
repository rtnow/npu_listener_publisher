#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16.hpp"

using std::placeholders::_1;

class GoalSubscriber : public rclcpp::Node{
  public:
    GoalSubscriber()
    : Node("GoalSubscriber")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int16>(
      "topic", 1, std::bind(&GoalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::Int16::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
    }
    rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscription_;};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GoalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
