#include "../include/px4_simulation_wrapper/px4_velocity_control_wrapper.h"

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "px4_velocity_control_wrapper");
  px4_velocity_control_wrapper control_wrapper;
  ros::spin();
  return 0;
}
