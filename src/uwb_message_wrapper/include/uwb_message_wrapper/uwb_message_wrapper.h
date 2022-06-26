#ifndef UWB_MESSAGE_WRAPPER_H
#define UWB_MESSAGE_WRAPPER_H
#include "ros/ros.h"
#include "nlink_parser/LinktrackNode0.h"
#include "nlink_parser/LinktrackNodeframe0.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Bool.h"
#include "iostream"
#include "vector"
#include "dt_message_package/uavs_pose_vel.h"
#include "std_msgs/String.h"
#include "uwb_common/uwb_common.h"
#include <sstream>
#include "string"
using namespace std;

typedef struct{
  float px;
  float py;
  float pz;
  float vx;
  float vy;
  float vz;
} PosVelStu;

class uwb_message_wrapper
{
public:
  uwb_message_wrapper();
  void uwbMsgSubCb(const nlink_parser::LinktrackNodeframe0ConstPtr& msg);
  void localPosMsgSubCb(const geometry_msgs::PoseStampedConstPtr& msg);
  void velMsgSubCb(const geometry_msgs::TwistStampedConstPtr& msg);
  void msgToOtherTimerCb(const ros::TimerEvent& event);
  void uavsPosVelPubTimerCb(const ros::TimerEvent& event);

private:
  ros::Subscriber _uwbMsgSub;
  ros::Subscriber _localPosMsgSub;
  ros::Subscriber _velMsgSub;

  ros::Publisher _uwbMsgPub;
  ros::Publisher _uavsPosVelMsgPub;
  ros::Publisher _networkStateMsgPub;
  ros::Publisher _targetObjPosMsgPub;

  bool IsJsonData(string data);
  string CheckRecvData(string msg);
  std::pair<PosVelStu,bool> getRecvData(string msg);
  string packData(PosVelStu data);
  std::pair<PosVelStu,bool> unpackData(string msg);

  bool _isCar;

  std::vector<PosVelStu> _posVels;

  int _uavNum;
  int _uavId;
  float _msgToOtherHz;
  float _uavsPosVelPubHz;

  float _startPositionX;
  float _startPositionY;
  float _startPositionZ;

  ros::Timer _msgToOtherTimer;
  ros::Timer _uavsPosVelPubTimer;


};

#endif // UWB_MESSAGE_WRAPPER_H
