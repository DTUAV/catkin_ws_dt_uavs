#include "../include/dt_simulation_wrapper/dt_simulation_wrapper.h"

dt_simulation_wrapper::dt_simulation_wrapper()
{
  ros::NodeHandle n("~");
  std::string UAV1PosSubTopic = "/UAV1/mavros/local_position/pose";
  n.getParam("UAV1LocalPositionMessageSubTopic",UAV1PosSubTopic);
  std::string UAV2PosSubTopic = "/UAV2/mavros/local_position/pose";
  n.getParam("UAV2LocalPositionMessageSubTopic",UAV2PosSubTopic);
  std::string UAV3PosSubTopic = "/UAV3/mavros/local_position/pose";
  n.getParam("UAV3LocalPositionMessageSubTopic",UAV3PosSubTopic);
  std::string UAV4PosSubTopic = "/UAV4/mavros/local_position/pose";
  n.getParam("UAV4LocalPositionMessageSubTopic",UAV4PosSubTopic);
  std::string UAV5PosSubTopic = "/UAV5/mavros/local_position/pose";
  n.getParam("UAV5LocalPositionMessageSubTopic",UAV5PosSubTopic);
  std::string UAV6PosSubTopic = "/UAV6/mavros/local_position/pose";
  n.getParam("UAV6LocalPositionMessageSubTopic",UAV6PosSubTopic);
  std::string UAV7PosSubTopic = "/UAV7/mavros/local_position/pose";
  n.getParam("UAV7LocalPositionMessageSubTopic",UAV7PosSubTopic);

  std::string UAV1VelSubTopic = "/UAV1/mavros/local_position/velocity";
  n.getParam("UAV1LocalVelocityMessageSubTopic",UAV1VelSubTopic);
  std::string UAV2VelSubTopic = "/UAV2/mavros/local_position/velocity";
  n.getParam("UAV2LocalVelocityMessageSubTopic",UAV2VelSubTopic);
  std::string UAV3VelSubTopic = "/UAV3/mavros/local_position/velocity";
  n.getParam("UAV3LocalVelocityMessageSubTopic",UAV3VelSubTopic);
  std::string UAV4VelSubTopic = "/UAV4/mavros/local_position/velocity";
  n.getParam("UAV4LocalVelocityMessageSubTopic",UAV4VelSubTopic);
  std::string UAV5VelSubTopic = "/UAV5/mavros/local_position/velocity";
  n.getParam("UAV5LocalVelocityMessageSubTopic",UAV5VelSubTopic);
  std::string UAV6VelSubTopic = "/UAV6/mavros/local_position/velocity";
  n.getParam("UAV6LocalVelocityMessageSubTopic",UAV6VelSubTopic);

  std::string UAVsPosVelPubTopic = "/other_uavs/state";
  n.getParam("UAVsPosVelMessagePubTopic",UAVsPosVelPubTopic);

  if(!n.getParam("MessagePubFrequency",_msgPubHz))
  {
    _msgPubHz = 10;
  }

  _uav1_pose_sub = n.subscribe(UAV1PosSubTopic,5,&dt_simulation_wrapper::uav1_local_pos_sub_cb,this);
  _uav2_pose_sub = n.subscribe(UAV2PosSubTopic,5,&dt_simulation_wrapper::uav2_local_pos_sub_cb,this);
  _uav3_pose_sub = n.subscribe(UAV3PosSubTopic,5,&dt_simulation_wrapper::uav3_local_pos_sub_cb,this);
  _uav4_pose_sub = n.subscribe(UAV4PosSubTopic,5,&dt_simulation_wrapper::uav4_local_pos_sub_cb,this);
  _uav5_pose_sub = n.subscribe(UAV5PosSubTopic,5,&dt_simulation_wrapper::uav5_local_pos_sub_cb,this);
  _uav6_pose_sub = n.subscribe(UAV6PosSubTopic,5,&dt_simulation_wrapper::uav6_local_pos_sub_cb,this);

  _uav1_vel_sub = n.subscribe(UAV1VelSubTopic,5,&dt_simulation_wrapper::uav1_vel_info_sub_cb,this);
  _uav2_vel_sub = n.subscribe(UAV2VelSubTopic,5,&dt_simulation_wrapper::uav2_vel_info_sub_cb,this);
  _uav3_vel_sub = n.subscribe(UAV3VelSubTopic,5,&dt_simulation_wrapper::uav3_vel_info_sub_cb,this);
  _uav4_vel_sub = n.subscribe(UAV4VelSubTopic,5,&dt_simulation_wrapper::uav4_vel_info_sub_cb,this);
  _uav5_vel_sub = n.subscribe(UAV5VelSubTopic,5,&dt_simulation_wrapper::uav5_vel_info_sub_cb,this);
  _uav6_vel_sub = n.subscribe(UAV6VelSubTopic,5,&dt_simulation_wrapper::uav6_vel_info_sub_cb,this);

  _uavs_pos_vel_pub = n.advertise<dt_message_package::uavs_pose_vel>(UAVsPosVelPubTopic,10);



  int flag_thread = pthread_create(&_runThread,NULL,&dt_simulation_wrapper::run,this);
  if (flag_thread < 0) {
    ROS_ERROR("message_wrapper--pthread_create ros_process_thread failed: %d\n", flag_thread);
  }

}

void *dt_simulation_wrapper::run(void *args)
{
  dt_simulation_wrapper* ptr = (dt_simulation_wrapper*)(args);
  ros::Rate rate(ptr->_msgPubHz);
  dt_message_package::uavs_pose_vel pubMsg;
  pubMsg.position.resize(6);
  pubMsg.uav_id = {1,2,3,4,5,6};
  pubMsg.velocity.resize(6);
  while(ros::ok())
  {
    pubMsg.position.at(0) = ptr->_uav1_pose.pose.position;
    pubMsg.position.at(1) = ptr->_uav2_pose.pose.position;
    pubMsg.position.at(2) = ptr->_uav3_pose.pose.position;
    pubMsg.position.at(3) = ptr->_uav4_pose.pose.position;
    pubMsg.position.at(4) = ptr->_uav5_pose.pose.position;
    pubMsg.position.at(5) = ptr->_uav6_pose.pose.position;

    pubMsg.velocity.at(0) = ptr->_uav1_vel.twist.linear;
    pubMsg.velocity.at(1) = ptr->_uav2_vel.twist.linear;
    pubMsg.velocity.at(2) = ptr->_uav3_vel.twist.linear;
    pubMsg.velocity.at(3) = ptr->_uav4_vel.twist.linear;
    pubMsg.velocity.at(4) = ptr->_uav5_vel.twist.linear;
    pubMsg.velocity.at(5) = ptr->_uav6_vel.twist.linear;

    ptr->_uavs_pos_vel_pub.publish(pubMsg);
    rate.sleep();
  }
  delete ptr;
  pthread_join(ptr->_runThread,NULL);
}
void dt_simulation_wrapper::uav1_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav1_pose = *msg;
}
void dt_simulation_wrapper::uav1_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav1_vel = *msg;
}

void dt_simulation_wrapper::uav2_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav2_pose = *msg;
}
void dt_simulation_wrapper::uav2_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav2_vel = *msg;
}

void dt_simulation_wrapper::uav3_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav3_pose = *msg;
}
void dt_simulation_wrapper::uav3_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav3_vel = *msg;
}

void dt_simulation_wrapper::uav4_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav4_pose = *msg;
}
void dt_simulation_wrapper::uav4_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav4_vel = *msg;
}

void dt_simulation_wrapper::uav5_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav5_pose = *msg;
}
void dt_simulation_wrapper::uav5_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav5_vel = *msg;
}

void dt_simulation_wrapper::uav6_local_pos_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  _uav6_pose = *msg;
}
void dt_simulation_wrapper::uav6_vel_info_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  _uav6_vel = *msg;
}


