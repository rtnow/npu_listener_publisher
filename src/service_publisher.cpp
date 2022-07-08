#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int16.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a* member function as a callback from the timer. */

class Ps2_Publisher : public rclcpp::Node{
  public:
    Ps2_Publisher()
    : Node("Ps2_Publisher")
    {
      publisher_ = this->create_publisher<std_msgs::msg::Int16>("service", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Ps2_Publisher::timer_callback, this));
    }


  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Int16();
      //message.data = "Hello, world! " + std::to_string(count_++);
      message.data = -1;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher_;
    //size_t count_;
  };


  int main(int argc, char * argv[])
  {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Ps2_Publisher>());
    rclcpp::shutdown();
    return 0;
  }
