#include "../include/uwb_message_wrapper/uwb_message_wrapper.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "uwb_message_wrapper_main");
  ros::NodeHandle nh;
  uwb_message_wrapper  node;
  ros::MultiThreadedSpinner spinner(2); // Use 2 threads
  //std::cout<<std::stof("2d0.d03ddd")<<std::endl;
  spinner.spin(); // spin

  ROS_INFO("Hello world!");
}
