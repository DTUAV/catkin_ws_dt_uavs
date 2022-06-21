#ifndef DT_SIMULATION_WRAPPER_H
#define DT_SIMULATION_WRAPPER_H
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <dt_message_package/uavs_pose_vel.h>
#include <unordered_set>

class dt_simulation_wrapper
{
public:
  dt_simulation_wrapper();
  static void *run(void *args);
  void uav1_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav1_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

  void uav2_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav2_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

  void uav3_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav3_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

  void uav4_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav4_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

  void uav5_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav5_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

  void uav6_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void uav6_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);

private:
  ros::Subscriber _uav1_pose_sub;
  ros::Subscriber _uav2_pose_sub;
  ros::Subscriber _uav3_pose_sub;
  ros::Subscriber _uav4_pose_sub;
  ros::Subscriber _uav5_pose_sub;
  ros::Subscriber _uav6_pose_sub;

  ros::Subscriber _uav1_vel_sub;
  ros::Subscriber _uav2_vel_sub;
  ros::Subscriber _uav3_vel_sub;
  ros::Subscriber _uav4_vel_sub;
  ros::Subscriber _uav5_vel_sub;
  ros::Subscriber _uav6_vel_sub;

  ros::Publisher _uavs_pos_vel_pub;

  geometry_msgs::PoseStamped _uav1_pose;
  geometry_msgs::PoseStamped _uav2_pose;
  geometry_msgs::PoseStamped _uav3_pose;
  geometry_msgs::PoseStamped _uav4_pose;
  geometry_msgs::PoseStamped _uav5_pose;
  geometry_msgs::PoseStamped _uav6_pose;

  geometry_msgs::TwistStamped _uav1_vel;
  geometry_msgs::TwistStamped _uav2_vel;
  geometry_msgs::TwistStamped _uav3_vel;
  geometry_msgs::TwistStamped _uav4_vel;
  geometry_msgs::TwistStamped _uav5_vel;
  geometry_msgs::TwistStamped _uav6_vel;

};

#endif // DT_SIMULATION_WRAPPER_H














