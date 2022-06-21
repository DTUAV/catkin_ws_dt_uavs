#include "../include/dt_target_object/dt_target_object.h"

dt_target_object::dt_target_object()
{
  ros::NodeHandle n("~");
  if(!n.getParam("SourceID",_sourceID))
  {
    _sourceID = 0;
    std::cout<<"dt_target_object--SourceID No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--SourceID: "<<_sourceID<<std::endl;

  if(!n.getParam("TargetID",_targetID))
  {
    _targetID = 100;
    std::cout<<"dt_target_object--TargetID No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--TargetID: "<<_targetID<<std::endl;

  if(!n.getParam("DtObjectID",_dtObjectID))
  {
    _dtObjectID = 100;
    std::cout<<"dt_target_object--DtObjectID No Configure"<<_dtObjectID<<std::endl;
  }
  std::cout<<"dt_target_object--DtObjectID: "<<_dtObjectID<<std::endl;

  std::string CloudMsgSubTopic = "/R_UAV_0/Message_from_Cloud";
  if(!n.getParam("CloudMessageSubTopic",CloudMsgSubTopic))
  {
    std::cout<<"dt_target_object--CloudMessageSubTopic No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--CloudMessageSubTopic: "<<CloudMsgSubTopic<<std::endl;

  std::string LocalPosMsgSubTopic = "/mavros/local_position/pose";
  if(!n.getParam("LocalPositionMessageSubTopic",LocalPosMsgSubTopic))
  {
    std::cout<<"dt_target_object--LocalPositionMessageSubTopic No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--LocalPositionMessageSubTopic: "<<LocalPosMsgSubTopic<<std::endl;

  if(!n.getParam("MessagePubFrequency",_msgPubHz))
  {
    _msgPubHz = 10;
    std::cout<<"dt_target_object--MessagePubFrequency No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--MessagePubFrequency: "<<_msgPubHz<<std::endl;

  if(!n.getParam("StartPositionX",_startPosX))
  {
    _startPosX = 0;
    std::cout<<"dt_target_object--StartPositionX No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--StartPositionX: "<<_startPosX<<std::endl;

  if(!n.getParam("StartPositionY",_startPosY))
  {
    _startPosY = 0;
    std::cout<<"dt_target_object--StartPositionY No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--StartPositionY: "<<_startPosY<<std::endl;

  if(!n.getParam("StartPositionZ",_startPosZ))
  {
    _startPosZ = 0;
    std::cout<<"dt_target_object--StartPositionZ No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--StartPositionZ: "<<_startPosZ<<std::endl;

  std::string TargetVelPubTopic = "/R_UAV_0/Target/Velocity";
  if(!n.getParam("TargetVelocityMessagePubTopic",TargetVelPubTopic))
  {
    std::cout<<"dt_target_object--TargetVelocityMessagePubTopic No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--TargetVelocityMessagePubTopic: "<<TargetVelPubTopic<<std::endl;

  std::string CloudMsgPubTopic = "/R_UAV_0/Message_to_Cloud";
  if(!n.getParam("CloudMessagePubTopic",CloudMsgPubTopic))
  {
    std::cout<<"dt_target_object--CloudMessagePubTopic No Configure"<<std::endl;
  }
  std::cout<<"dt_target_object--CloudMessagePubTopic: "<<CloudMsgPubTopic<<std::endl;

  _localPoseSub = n.subscribe(LocalPosMsgSubTopic,1,&dt_target_object::localPosSubCb,this);
  _cloudMsgSub = n.subscribe(CloudMsgSubTopic,1,&dt_target_object::cloudMsgCb,this);

  _cloudMsgPub = n.advertise<dt_message_package::CloudMessage>(CloudMsgPubTopic,1);
  _targetVelPub = n.advertise<geometry_msgs::TwistStamped>(TargetVelPubTopic,1);

  int flag_thread = pthread_create(&_runThread,NULL,&dt_target_object::run,this);
  if (flag_thread < 0) {
    ROS_ERROR("dt_target_object--pthread_create ros_process_thread failed: %d\n", flag_thread);
  }


}
void *dt_target_object::run(void *args)
{
  dt_target_object* ptr = (dt_target_object*)(args);
  ros::Rate rate(ptr->_msgPubHz);
  dt_message_package::CloudMessage pubMsg;
  pubMsg.SourceID = ptr->_sourceID;
  pubMsg.TargetID = ptr->_targetID;
  pubMsg.MessageID =TargetObjectPoseMessageID;
  TargetObjPoseMessage msg;
  while(ros::ok())
  {
    {
      std::lock_guard<mutex> guard(ptr->m);
      msg.posX = ptr->_localPose.pose.position.x + ptr->_startPosX;
      msg.posY = ptr->_localPose.pose.position.y + ptr->_startPosY;
      msg.posZ = ptr->_localPose.pose.position.z + ptr->_startPosZ;

      msg.rotX = ptr->_localPose.pose.orientation.x;
      msg.rotY = ptr->_localPose.pose.orientation.y;
      msg.rotZ = ptr->_localPose.pose.orientation.z;
      msg.rotW = ptr->_localPose.pose.orientation.w;
    }
    pubMsg.TimeStamp = ros::Time::now().toNSec();
    pubMsg.MessageData = x2struct::X::tojson(msg);
    ptr->_cloudMsgPub.publish(pubMsg);
    rate.sleep();
  }
  pthread_join(ptr->_runThread,NULL);
}
void dt_target_object::cloudMsgCb(const dt_message_package::CloudMessageConstPtr &msg)
{
  switch (msg.get()->MessageID) {
  case UavControlID:
  {
    UavControl uavControlMsg;
    bool isLoad = x2struct::X::loadjson(msg.get()->MessageData,uavControlMsg,false);
    if(isLoad)
    {
       if(uavControlMsg.Mode==1)
      {
        //velocity mode
        geometry_msgs::TwistStamped targetVelMsg;
        targetVelMsg.header.stamp = ros::Time::now();
        targetVelMsg.twist.linear.x = uavControlMsg.ComLX;
        targetVelMsg.twist.linear.y = uavControlMsg.ComLY;
        targetVelMsg.twist.linear.z = uavControlMsg.ComLZ;
        targetVelMsg.twist.angular.x = uavControlMsg.ComAX;
        targetVelMsg.twist.angular.y = uavControlMsg.ComAY;
        targetVelMsg.twist.angular.z = uavControlMsg.ComAZ;
        _targetVelPub.publish(targetVelMsg);
        //std::cout<<"dddddd"<<std::endl;
      }
    }
    else
      ROS_INFO("Unpack UavControl Message Fail!!!");
  }
    break;
  default:
    break;
  }
}

void dt_target_object::localPosSubCb(const geometry_msgs::PoseStampedConstPtr &msg)
{
  std::lock_guard<mutex> guard(m);
  _localPose = *msg;
}

