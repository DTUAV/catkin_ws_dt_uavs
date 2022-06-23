#include "../include/uwb_message_wrapper/uwb_message_wrapper.h"

bool uwb_message_wrapper::IsJsonData(string data)
{
  if(data[0] != '{')
    return false;
  int num = 1;
  for(int i=1;i<data.length();++i)
  {
    if(data[i] == '{')
    {
      ++num;
      // cout<<"true json "<<i<<data[i]<<endl;
    }
    else if(data[i] =='}')
    {
      --num;
      //cout<<"true json "<<i<<data[i]<<endl;
    }
    if(num == 0&&data[data.length()-1] =='}')
    {
      // cout<<"true json"<<"  sucess"<<endl;
      return true;

    }
  }
  return false;
  //cout<<"true json"<<"  fali"<<endl;

}
string uwb_message_wrapper::CheckRecvData(string msg)
{
  string ret;
  if(msg[0] != '{')
  {
    ret = "";
  }
  else
  {
    int num = 0;
    for(int i=0;i<msg.length();i++)
    {
      if(msg[i] =='}')
      {
        num++;
      }
      if(num == 2)
      {
        ret = msg.substr(0,i+1);
        break;
      }
    }
  }
  return ret;
}

uwb_message_wrapper::uwb_message_wrapper()
{
  ros::NodeHandle n("~");
  std::string UwbMsgSubTopic = "/uwb/msg_from_other";
  n.getParam("UwbMsgSubTopic",UwbMsgSubTopic);

  std::string UwbMsgPubTopic = "/uwb/msg_to_other";
  n.getParam("UwbMsgPubTopic",UwbMsgPubTopic);

  std::string UavLocalPosSubTopic = "/mavros/local_position/pose";
  n.getParam("UavLocalPosSubTopic",UavLocalPosSubTopic);

  std::string UavVelSubTopic = "/mavros/local_position/velocity";
  n.getParam("UavVelSubTopic",UavVelSubTopic);

  _uavNum = 6;
  n.getParam("UavNum",_uavNum);

  _msgToOtherHz = 30.0;
  n.getParam("MsgToOtherHz",_msgToOtherHz);

  _uavId = 1;
  n.getParam("UavId",_uavId);

  _uavsPosVelPubHz = 30.0;
  n.getParam("UavsPosVelPubHz",_uavsPosVelPubHz);

  std::string UavsPosVelPubTopic = "/other_uav/state";
  n.getParam("UavsPosVelPubTopic",UavsPosVelPubTopic);

  std::string NetworkStatePubTopic = "/network/state";
  n.getParam("NetworkStatePubTopic",NetworkStatePubTopic);

  _startPositionX = 0;
  n.getParam("StartPositionX",_startPositionX);

  _startPositionY = 0;
  n.getParam("StartPositionY",_startPositionY);

  _startPositionZ = 0;
  n.getParam("StartPositionZ",_startPositionZ);

  std::string TargetObjectPosPubTopic = "/target/object/pose";
  n.getParam("TargetObjectPosPubTopic",TargetObjectPosPubTopic);

  _posVels.resize(_uavNum+1);
  _recvTime = 0;
  _isGetMsg = false;
  _uwbMsgSub = n.subscribe(UwbMsgSubTopic,1,&uwb_message_wrapper::uwbMsgSubCb,this);
  _localPosMsgSub = n.subscribe(UavLocalPosSubTopic,1,&uwb_message_wrapper::localPosMsgSubCb,this);
  _velMsgSub = n.subscribe(UavVelSubTopic,1,&uwb_message_wrapper::velMsgSubCb,this);

  _uwbMsgPub = n.advertise<std_msgs::String>(UwbMsgPubTopic,5);
  _uavsPosVelMsgPub = n.advertise<dt_message_package::uavs_pose_vel>(UavsPosVelPubTopic,5);
  _networkStateMsgPub = n.advertise<std_msgs::Bool>(NetworkStatePubTopic,5);
  _targetObjPosMsgPub = n.advertise<geometry_msgs::PoseStamped>(TargetObjectPosPubTopic,5);


  _msgToOtherTimer   = n.createTimer(ros::Duration(1/_msgToOtherHz), &uwb_message_wrapper::msgToOtherTimerCb, this);
  _uavsPosVelPubTimer = n.createTimer(ros::Duration(1/_uavsPosVelPubHz),&uwb_message_wrapper::UavsPosVelPubTimerCb,this);

}

void uwb_message_wrapper::uwbMsgSubCb(const nlink_parser::LinktrackNodeframe0ConstPtr &msg)
{
  std_msgs::Bool stateMsg;
  stateMsg.data = true;
  _networkStateMsgPub.publish(stateMsg);
  for(int i=0;i<msg.get()->nodes.size();++i)
  {
    std::string msgData = msg.get()->nodes.at(i).data;
    int id = msg.get()->nodes.at(i).id;
    bool isjson;
    if(isjson = IsJsonData(msgData) == true)
    {
      UavPosVelMessage posvelMsg;
      bool is_load = x2struct::X::loadjson(msgData,posvelMsg,false);
      if(is_load){
        _posVels.at(id-1).px = posvelMsg.px;
        _posVels.at(id-1).py = posvelMsg.py;
        _posVels.at(id-1).pz = posvelMsg.pz;
        _posVels.at(id-1).vx = posvelMsg.vx;
        _posVels.at(id-1).vy = posvelMsg.vy;
        _posVels.at(id-1).vz = posvelMsg.vz;
      }
    }
  }
}

void uwb_message_wrapper::localPosMsgSubCb(const geometry_msgs::PoseStampedConstPtr &msg)
{
  _posVels.at(_uavId-1).px = msg.get()->pose.position.x;
  _posVels.at(_uavId-1).py = msg.get()->pose.position.y;
  _posVels.at(_uavId-1).pz = msg.get()->pose.position.z;
}

void uwb_message_wrapper::velMsgSubCb(const geometry_msgs::TwistStampedConstPtr &msg)
{
  _posVels.at(_uavId-1).vx = msg.get()->twist.linear.x;
  _posVels.at(_uavId-1).vy = msg.get()->twist.linear.y;
  _posVels.at(_uavId-1).vz = msg.get()->twist.linear.z;
}

void uwb_message_wrapper::msgToOtherTimerCb(const ros::TimerEvent &event)
{
  UavPosVelMessage msg;
  msg.px = _posVels.at(_uavId-1).px+_startPositionX;
  msg.py = _posVels.at(_uavId-1).py+_startPositionY;
  msg.pz = _posVels.at(_uavId-1).pz+_startPositionZ;
  msg.vx = _posVels.at(_uavId-1).vx;
  msg.vy = _posVels.at(_uavId-1).vy;
  msg.vz = _posVels.at(_uavId-1).vz;
  std::string msgData = x2struct::X::tojson(msg);
  std_msgs::String pubMsg;
  pubMsg.data = msgData;

}

void uwb_message_wrapper::uavsPosVelPubTimerCb(const ros::TimerEvent &event)
{
  dt_message_package::uavs_pose_vel msg;
  msg.header.frame_id ="uavs";
  msg.header.stamp = ros::Time::now();
  msg.uav_id.resize(_posVels.size());
  msg.position.resize(_posVels.size());
  msg.velocity.resize(_posVels.size());
  for(int i = 0;i<_uavNum;++i)
  {
    msg.uav_id.at(i) = i+1;
    msg.position.at(i).x = _posVels.at(i).px;
    msg.position.at(i).y = _posVels.at(i).py;
    msg.position.at(i).z = _posVels.at(i).pz;
    msg.velocity.at(i).x = _posVels.at(i).vx;
    msg.velocity.at(i).y = _posVels.at(i).vy;
    msg.velocity.at(i).z = _posVels.at(i).vz;
  }
  _uavsPosVelMsgPub.publish(msg);

  geometry_msgs::PoseStamped targetObjPosMsg;
  targetObjPosMsg.pose.position.x = _posVels.at(_uavNum).px;
  targetObjPosMsg.pose.position.y = _posVels.at(_uavNum).py;
  targetObjPosMsg.pose.position.z = _posVels.at(_uavNum).pz;
  targetObjPosMsg.header.frame_id = "target_object";
  targetObjPosMsg.header.stamp = ros::Time::now();
  _targetObjPosMsgPub.publish(targetObjPosMsg);
}









