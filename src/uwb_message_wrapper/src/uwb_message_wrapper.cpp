#include "../include/uwb_message_wrapper/uwb_message_wrapper.h"

string uwb_message_wrapper::packData(PosVelStu data)
{
  string ret = "{";
  ret += std::to_string(data.px);
  ret += ",";
  ret += std::to_string(data.py);
  ret += ",";
  ret += std::to_string(data.pz);
  ret += ",";
  ret += std::to_string(data.vx);
  ret += ",";
  ret += std::to_string(data.vy);
  ret += ",";
  ret += std::to_string(data.vz);
  ret += "}";
  return ret;
}

std::pair<PosVelStu,bool> uwb_message_wrapper::unpackData(string msg)
{

}

std::pair<PosVelStu,bool> uwb_message_wrapper::getRecvData(string msg)
{
  std::pair<PosVelStu,bool> ret;
  ret.second = false;
  int dotSize = 5;
  int indexSize = 6;
  vector<int> dotPos;
  vector<int> indexPos;
  for(int i=0;i<msg.size();++i){
    if(msg.at(i)==',') {dotSize--;dotPos.push_back(i);}
    if(msg.at(i)==':') {indexSize--;indexPos.push_back(i+1);}
  }
  if(dotSize==0&&indexSize==0){
    ret.second = true;
    dotPos.push_back(msg.size()-1);
    ret.first.px = std::stof(msg.substr(indexPos.at(0),dotPos.at(0)-indexPos.at(0)));
    ret.first.py = std::stof(msg.substr(indexPos.at(1),dotPos.at(1)-indexPos.at(1)));
    ret.first.pz = std::stof(msg.substr(indexPos.at(2),dotPos.at(2)-indexPos.at(2)));
    ret.first.vx = std::stof(msg.substr(indexPos.at(3),dotPos.at(3)-indexPos.at(3)));
    ret.first.vy = std::stof(msg.substr(indexPos.at(4),dotPos.at(4)-indexPos.at(4)));
    ret.first.vz = std::stof(msg.substr(indexPos.at(5),dotPos.at(5)-indexPos.at(5)));
  }
  return ret;
}

bool uwb_message_wrapper::IsJsonData(string data)
{
  if(data[0] != '{')
    return false;
  int num = 1;
  int dotNum = 12;
  for(int i=1;i<data.length();++i)
  {
    if(data[i] == '"') dotNum--;

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
    if(num == 0&&data[data.length()-1] =='}') break;
  }
  if(dotNum==0&&num == 0&&data[data.length()-1] =='}')
  {
    // cout<<"true json"<<"  sucess"<<endl;
    return true;
  }
  else
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
      if(num == 1)
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

  _isCar = false;
  n.getParam("IsCar",_isCar);

  _posVels.resize(_uavNum+1);

  _uwbMsgSub = n.subscribe(UwbMsgSubTopic,1,&uwb_message_wrapper::uwbMsgSubCb,this);
  _localPosMsgSub = n.subscribe(UavLocalPosSubTopic,1,&uwb_message_wrapper::localPosMsgSubCb,this);
  _velMsgSub = n.subscribe(UavVelSubTopic,1,&uwb_message_wrapper::velMsgSubCb,this);

  _uwbMsgPub = n.advertise<std_msgs::String>(UwbMsgPubTopic,5);
  _uavsPosVelMsgPub = n.advertise<dt_message_package::uavs_pose_vel>(UavsPosVelPubTopic,5);
  _networkStateMsgPub = n.advertise<std_msgs::Bool>(NetworkStatePubTopic,5);
  _targetObjPosMsgPub = n.advertise<geometry_msgs::PoseStamped>(TargetObjectPosPubTopic,5);


  _msgToOtherTimer   = n.createTimer(ros::Duration(1/_msgToOtherHz), &uwb_message_wrapper::msgToOtherTimerCb, this);
  _uavsPosVelPubTimer = n.createTimer(ros::Duration(1/_uavsPosVelPubHz),&uwb_message_wrapper::uavsPosVelPubTimerCb,this);

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
    if(IsJsonData(msgData))
    {
      msgData = CheckRecvData(msgData);
      if(msgData!=""){
        std::pair<PosVelStu,bool> posvelMsg = getRecvData(msgData);
        if(posvelMsg.second){
          _posVels.at(id-1).px = posvelMsg.first.px;
          _posVels.at(id-1).py = posvelMsg.first.py;
          _posVels.at(id-1).pz = posvelMsg.first.pz;
          _posVels.at(id-1).vx = posvelMsg.first.vx;
          _posVels.at(id-1).vy = posvelMsg.first.vy;
          _posVels.at(id-1).vz = posvelMsg.first.vz;
        }
      }else{std::cout<<"msgData=null"<<std::endl;}
    }else{std::cout<<"is not Json Data"<<std::endl;}
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
  _uwbMsgPub.publish(pubMsg);
}

void uwb_message_wrapper::uavsPosVelPubTimerCb(const ros::TimerEvent &event)
{
  dt_message_package::uavs_pose_vel msg;
  msg.header.frame_id ="uavs";
  msg.header.stamp = ros::Time::now();
  int num = 0;
  if(_isCar) num = _uavNum+1;
  else num = _uavNum;
  msg.uav_id.resize(num);
  msg.position.resize(num);
  msg.velocity.resize(num);

  for(int i = 0;i<num;++i)
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









