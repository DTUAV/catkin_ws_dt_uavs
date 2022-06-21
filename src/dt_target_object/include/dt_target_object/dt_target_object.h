#ifndef DT_TARGET_OBJECT_H
#define DT_TARGET_OBJECT_H
#include "ros/ros.h"
#include "iostream"
#include <dt_common/define_common.h>
#include <geometry_msgs/PoseStamped.h>
#include "x2struct/x2struct.hpp"
#include <dt_message_package/CloudMessage.h>
#include "pthread.h"
#include <mutex>
#include <geometry_msgs/TwistStamped.h>
using namespace DTUAV;

class dt_target_object
{
public:
  dt_target_object();
  static void *run(void *args);
  void localPosSubCb(const geometry_msgs::PoseStampedConstPtr& msg);
  void cloudMsgCb(const dt_message_package::CloudMessageConstPtr& msg);

private:
  ros::Subscriber _localPoseSub;
  ros::Subscriber _cloudMsgSub;

  ros::Publisher _cloudMsgPub;
  ros::Publisher _targetVelPub;

  geometry_msgs::PoseStamped _localPose;

  int _sourceID;
  int _targetID;
  int _dtObjectID;

  float _startPosX;
  float _startPosY;
  float _startPosZ;

  pthread_t _runThread;
  float _msgPubHz;
  std::mutex m;
};

#endif // DT_TARGET_OBJECT_H
