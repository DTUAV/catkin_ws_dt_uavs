#include "uavs_main_window.h"
#include "ui_uavs_main_window.h"

uavs_main_window::uavs_main_window(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::uavs_main_window)
{
  ui->setupUi(this);
  uav_info_class_ptr = make_shared<UAVInfoClass>(all_info);
  m_nTimerID = this->startTimer(500);//500ms
  ros::NodeHandle n("~");
  std::string networkMsgSubName = "/Server1/Message_From_Cloud";
  n.getParam("NetworkMsgSubName",networkMsgSubName);
  std::string networkMsgPubName = "/Server1/Message_To_Cloud";
  n.getParam("NetworkMsgPubName",networkMsgPubName);
  _heartMsgHz = 0.5;
  n.getParam("HeartMsgHz",_heartMsgHz);
  _objectID = 1;
  _networkMsgSub = n.subscribe(networkMsgSubName,100,&uavs_main_window::network_msg_sub_cb,this);
  _networkMsgPub = n.advertise<dt_message_package::CloudMessage>(networkMsgPubName,100);
  network_pub_ptr = make_shared<ros::Publisher>(_networkMsgPub);
  int flag_thread = pthread_create(&_heartMsgPubTh, NULL, &uavs_main_window::run_pub_heart_msg, this);
    if (flag_thread < 0) {
      ROS_ERROR("pthread_create ros_process_thread failed: %d\n", flag_thread);
    }
}

void* uavs_main_window::run_pub_heart_msg(void *value)
{
  uavs_main_window* uavs_win = (uavs_main_window*)(value);
  ros::Rate rate(uavs_win->_heartMsgHz);
  HeartMsg hitMsg;
  hitMsg.is_get = true;
  dt_message_package::CloudMessage cloudMsg;
  cloudMsg.SourceID = Gloal_Server_0;
  cloudMsg.MessageID = HeartMsgID;
  cloudMsg.MessageData = x2struct::X::tojson(hitMsg);
  while(ros::ok())
  {
    cloudMsg.TimeStamp = ros::Time::now().toNSec();
    {
      std::lock_guard<mutex> guard(uavs_win->m);
      uavs_win->all_info._uav1Info.IsStart = false;
      uavs_win->all_info._uav2Info.IsStart = false;
      uavs_win->all_info._uav3Info.IsStart = false;
      uavs_win->all_info._uav4Info.IsStart = false;
      uavs_win->all_info._uav5Info.IsStart = false;
      uavs_win->all_info._uav6Info.IsStart = false;
      uavs_win->all_info._uav7Info.IsStart = false;
      uavs_win->all_info._uav8Info.IsStart = false;
      uavs_win->all_info._uav9Info.IsStart = false;
      uavs_win->all_info._uav10Info.IsStart = false;

      for(int i=1;i<=10;++i)
        uavs_win->all_info._uavLinkStatus.at(i-1) = false;

    }
    for(int i=1;i<=10;++i)
    {
      cloudMsg.TargetID = i;
      uavs_win->_networkMsgPub.publish(cloudMsg);
    }
    rate.sleep();
  }
}

void uavs_main_window::timerEvent(QTimerEvent *event)
{
  if(event->timerId() == m_nTimerID){
    ui_update_timeout();
  }
}
std::string uavs_main_window::packVector3(double x, double y, double z)
{
  std::string ret = "( "+ std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")";
  return ret;
}

void uavs_main_window::resetAllFlightMode()
{
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::white);
  ui->manual->setAutoFillBackground(true);
  ui->manual->setPalette(palette);

  ui->stabilizing->setAutoFillBackground(true);
  ui->stabilizing->setPalette(palette);

  ui->altitude->setAutoFillBackground(true);
  ui->altitude->setPalette(palette);

  ui->position->setAutoFillBackground(true);
  ui->position->setPalette(palette);

  ui->offboard->setAutoFillBackground(true);
  ui->offboard->setPalette(palette);

  ui->return_2->setAutoFillBackground(true);
  ui->return_2->setPalette(palette);
}

void uavs_main_window::resetAllSelectBt()
{
  ui->pb_uav1->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav2->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav3->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav4->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav5->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav6->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav7->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav8->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav9->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uav10->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_uavall->setStyleSheet("background-color: rgb(255,255,255)");
  /*
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::white);

  ui->pb_uav1->setAutoFillBackground(true);
  ui->pb_uav1->setPalette(palette);

  ui->pb_uav2->setAutoFillBackground(true);
  ui->pb_uav2->setPalette(palette);

  ui->pb_uav3->setAutoFillBackground(true);
  ui->pb_uav3->setPalette(palette);

  ui->pb_uav4->setAutoFillBackground(true);
  ui->pb_uav4->setPalette(palette);

  ui->pb_uav5->setAutoFillBackground(true);
  ui->pb_uav5->setPalette(palette);

  ui->pb_uav6->setAutoFillBackground(true);
  ui->pb_uav6->setPalette(palette);

  ui->pb_uav7->setAutoFillBackground(true);
  ui->pb_uav7->setPalette(palette);

  ui->pb_uav8->setAutoFillBackground(true);
  ui->pb_uav8->setPalette(palette);

  ui->pb_uav9->setAutoFillBackground(true);
  ui->pb_uav9->setPalette(palette);

  ui->pb_uav10->setAutoFillBackground(true);
  ui->pb_uav10->setPalette(palette);
  */
}

void uavs_main_window::updateUi(const UavInfo &info)
{
  ui->pos->setText(QString::fromLocal8Bit(packVector3(info.PosX,info.PosY,info.PosZ).data()));
  ui->vel->setText(QString::fromLocal8Bit(packVector3(info.LVelX,info.LVelY,info.LVelZ).data()));
  tf::Quaternion quat;
  quat.setX(info.RotX),quat.setY(info.RotY),quat.setZ(info.RotZ),quat.setW(info.RotW);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  ui->att->setText(QString::fromLocal8Bit(packVector3(roll,pitch,yaw).data()));
  ui->att_rate->setText(QString::fromLocal8Bit(packVector3(info.AVelX,info.AVelY,info.AVelZ).data()));
  resetAllFlightMode();
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::green);

  switch (info.FMode) {
  case 0:
    ui->manual->setPalette(palette);
    break;
  case 1:
    ui->stabilizing->setPalette(palette);
    break;
  case 2:
    ui->altitude->setPalette(palette);
    break;
  case 3:
    ui->position->setPalette(palette);
    break;
  case 4:
    ui->offboard->setPalette(palette);
    break;
  case 5:
    ui->return_2->setPalette(palette);
    break;
  default:
    break;
  }
  /*
   * 0: the manual mode
   * 1: the stabilizing mode
   * 2: the altitude mode
   * 3: the position mode
   * 4: the offboard mode
   * 5: the return mode
   */
  if(info.NetPx4)
  {
    palette.setColor(QPalette::Background, Qt::green);
    ui->is_connect->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->is_connect->setPalette(palette);
  }
  if(info.IsArm)
  {
    palette.setColor(QPalette::Background,Qt::green);
    ui->is_arm->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->is_arm->setPalette(palette);
  }

  if(info.IsStart)
  {
    palette.setColor(QPalette::Background,Qt::green);
    ui->is_start->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->is_start->setPalette(palette);
  }

  ui->voltage->setText(QString::fromLocal8Bit(std::to_string(info.Voltage).data()));
  ui->remaining->setText(QString::fromLocal8Bit(std::to_string(info.Remaining).data()));

  ui->pb_is_arm->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_offboard_mode->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_position_mode->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_start->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_target_pos_ok->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_target_vel_ok->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_stop->setStyleSheet("background-color: rgb(255,255,255)");
}

void uavs_main_window::ui_update_timeout()
{
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::green);
  if(all_info._uavLinkStatus.at(_objectID-1))
  {
    palette.setColor(QPalette::Background, Qt::green);
    ui->is_link->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->is_link->setPalette(palette);
  }
  switch (_objectID) {
  case 1:
    updateUi(all_info._uav1Info);
    break;
  case 2:
    updateUi(all_info._uav2Info);
    break;
  case 3:
    updateUi(all_info._uav3Info);
    break;
  case 4:
    updateUi(all_info._uav4Info);
    break;
  case 5:
    updateUi(all_info._uav5Info);
    break;
  case 6:
    updateUi(all_info._uav6Info);
    break;
  case 7:
    updateUi(all_info._uav7Info);
    break;
  case 8:
    updateUi(all_info._uav8Info);
    break;
  case 9:
    updateUi(all_info._uav9Info);
    break;
  case 10:
    updateUi(all_info._uav10Info);
    break;
  default:
    break;
  }
}

uavs_main_window::~uavs_main_window()
{
  this->killTimer(m_nTimerID);
  delete ui;
}

void uavs_main_window::network_msg_sub_cb(const dt_message_package::CloudMessageConstPtr &msg)
{
  switch (msg.get()->MessageID) {
  case UavInfoID:
  {
    UavInfo uavInfoMsg;
    bool isLoad = x2struct::X::loadjson(msg.get()->MessageData,uavInfoMsg,false);
    if(isLoad)
    {
      all_info._uavLinkStatus.at(msg.get()->SourceID-1) = true;
      switch (msg.get()->SourceID) {
      case 1:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav1Info = uavInfoMsg;
      }
        break;
      case 2:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav2Info = uavInfoMsg;
      }
        break;
      case 3:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav3Info = uavInfoMsg;
      }
        break;
      case 4:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav4Info = uavInfoMsg;
      }
        break;
      case 5:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav5Info = uavInfoMsg;
      }
        break;
      case 6:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav6Info = uavInfoMsg;
      }
        break;
      case 7:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav7Info = uavInfoMsg;
      }
        break;
      case 8:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav8Info = uavInfoMsg;
      }
        break;
      case 9:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav9Info = uavInfoMsg;
      }
        break;
      case 10:
      {
        std::lock_guard<mutex> guard(m);
        all_info._uav10Info = uavInfoMsg;
      }
        break;
      default:
        break;
      }
    }
  }
    break;
  default:
    break;
  }
}

void uavs_main_window::on_pb_uav1_clicked()
{
  _objectID = 1;
  resetAllSelectBt();
  /*
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav1->setPalette(pe);
  */
  ui->pb_uav1->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav2_clicked()
{
  _objectID = 2;
  resetAllSelectBt();
  /*
  _objectID = 2;
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav2->setPalette(pe);
  */
  ui->pb_uav2->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav3_clicked()
{
  _objectID = 3;
  resetAllSelectBt();
  /*
  _objectID = 3;
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav3->setPalette(pe);
  */
  ui->pb_uav3->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav4_clicked()
{
  _objectID = 4;
  resetAllSelectBt();
  /*
  _objectID = 4;
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav4->setPalette(pe);
  */
  ui->pb_uav4->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav5_clicked()
{
  _objectID = 5;
  resetAllSelectBt();
  /*
  _objectID = 5;
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav5->setPalette(pe);
  */
  ui->pb_uav5->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav6_clicked()
{
  _objectID = 6;
  resetAllSelectBt();
  /*
  _objectID = 6;
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav6->setPalette(pe);
  */
  ui->pb_uav6->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav7_clicked()
{
  _objectID = 7;
  resetAllSelectBt();
  /*
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav7->setPalette(pe);
  */
  ui->pb_uav7->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav8_clicked()
{
  resetAllSelectBt();
  _objectID = 8;
  /*
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav8->setPalette(pe);
  */
  ui->pb_uav8->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav9_clicked()
{
  resetAllSelectBt();
  _objectID = 9;
  /*
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav9->setPalette(pe);
  */
  ui->pb_uav9->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uav10_clicked()
{
  resetAllSelectBt();
  _objectID = 10;
  /*
  QPalette pe;
  pe.setColor(QPalette::Background,Qt::green);
  resetAllSelectBt();
  ui->pb_uav10->setPalette(pe);
  */
  ui->pb_uav10->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_uavall_clicked()
{
  resetAllSelectBt();
  ui->pb_uavall->setStyleSheet("background-color: rgb(0,255,0)");
  all_uavs_windows* all_uavs_ui = new all_uavs_windows;
  all_uavs_ui->info_ptr = uav_info_class_ptr;
  all_uavs_ui->network_pub_ptr = network_pub_ptr;
  all_uavs_ui->show();
}

void uavs_main_window::on_pb_is_start_clicked()
{
  ui->pb_is_start->setStyleSheet("background-color: rgb(0,255,0)");
  UavCommand commandMsg;
  /*
   * 1:IsOffboard
   * 2:IsArm
   * 4:IsStart
   * 3:IsOffboard+IsArm
   * 5:IsOffboard+IsStart
   * 6:IsArm+IsStart
   * 7:IsOffboard+IsArm+IsStart
  */
  commandMsg.ComMode = 4;
  commandMsg.IsStart = true;
  dt_message_package::CloudMessage pubMsg;
  pubMsg.TimeStamp = ros::Time::now().toNSec();
  pubMsg.SourceID = Gloal_Server_0;
  pubMsg.TargetID = _objectID;
  pubMsg.MessageID = UavCommandID;
  pubMsg.MessageData = x2struct::X::tojson(commandMsg);
  _networkMsgPub.publish(pubMsg);

}

void uavs_main_window::on_pb_is_arm_clicked()
{
ui->pb_is_arm->setStyleSheet("background-color: rgb(0,255,0)");
UavCommand commandMsg;
/*
 * 1:IsOffboard
 * 2:IsArm
 * 4:IsStart
 * 3:IsOffboard+IsArm
 * 5:IsOffboard+IsStart
 * 6:IsArm+IsStart
 * 7:IsOffboard+IsArm+IsStart
*/
commandMsg.ComMode = 2;
commandMsg.IsArm = true;
dt_message_package::CloudMessage pubMsg;
pubMsg.TimeStamp = ros::Time::now().toNSec();
pubMsg.SourceID = Gloal_Server_0;
pubMsg.TargetID = _objectID;
pubMsg.MessageID = UavCommandID;
pubMsg.MessageData = x2struct::X::tojson(commandMsg);
_networkMsgPub.publish(pubMsg);

}

void uavs_main_window::on_pb_is_position_mode_clicked()
{
ui->pb_is_position_mode->setStyleSheet("background-color: rgb(0,255,0)");
}

void uavs_main_window::on_pb_is_offboard_mode_clicked()
{
ui->pb_is_offboard_mode->setStyleSheet("background-color: rgb(0,255,0)");
UavCommand commandMsg;
/*
 * 1:IsOffboard
 * 2:IsArm
 * 4:IsStart
 * 3:IsOffboard+IsArm
 * 5:IsOffboard+IsStart
 * 6:IsArm+IsStart
 * 7:IsOffboard+IsArm+IsStart
*/
commandMsg.ComMode = 1;
commandMsg.IsOffboard = true;
dt_message_package::CloudMessage pubMsg;
pubMsg.TimeStamp = ros::Time::now().toNSec();
pubMsg.SourceID = Gloal_Server_0;
pubMsg.TargetID = _objectID;
pubMsg.MessageID = UavCommandID;
pubMsg.MessageData = x2struct::X::tojson(commandMsg);
_networkMsgPub.publish(pubMsg);
}

void uavs_main_window::on_pb_target_pos_ok_clicked()
{
ui->pb_target_pos_ok->setStyleSheet("background-color: rgb(0,255,0)");
UavControl controlMsg;
controlMsg.Mode = 0;
controlMsg.ComLX = ui->target_pos_x->text().toDouble();
controlMsg.ComLY = ui->target_pos_y->text().toDouble();
controlMsg.ComLZ = ui->target_pos_z->text().toDouble();
controlMsg.ComAX = 0;
controlMsg.ComAY = 0;
controlMsg.ComAZ = ui->target_yaw->text().toDouble();;
dt_message_package::CloudMessage pubMsg;
pubMsg.TimeStamp = ros::Time::now().toNSec();
pubMsg.SourceID = Gloal_Server_0;
pubMsg.TargetID = _objectID;
pubMsg.MessageID = UavControlID;
pubMsg.MessageData = x2struct::X::tojson(controlMsg);
_networkMsgPub.publish(pubMsg);
}

void uavs_main_window::on_pb_target_vel_ok_clicked()
{
ui->pb_target_vel_ok->setStyleSheet("background-color: rgb(0,255,0)");
UavControl controlMsg;
controlMsg.Mode = 1;
controlMsg.ComLX = ui->target_vel_x->text().toDouble();
controlMsg.ComLY = ui->target_vel_y->text().toDouble();
controlMsg.ComLZ = ui->target_vel_z->text().toDouble();
controlMsg.ComAX = 0;
controlMsg.ComAY = 0;
controlMsg.ComAZ = ui->target_vel_yaw->text().toDouble();
dt_message_package::CloudMessage pubMsg;
pubMsg.TimeStamp = ros::Time::now().toNSec();
pubMsg.SourceID = Gloal_Server_0;
pubMsg.TargetID = _objectID;
pubMsg.MessageID = UavControlID;
pubMsg.MessageData = x2struct::X::tojson(controlMsg);
_networkMsgPub.publish(pubMsg);
}

void uavs_main_window::on_pb_is_stop_clicked()
{
    ui->pb_is_stop->setStyleSheet("background-color: rgb(0,255,0)");
    UavCommand commandMsg;
    /*
     * 1:IsOffboard
     * 2:IsArm
     * 4:IsStart
     * 3:IsOffboard+IsArm
     * 5:IsOffboard+IsStart
     * 6:IsArm+IsStart
     * 7:IsOffboard+IsArm+IsStart
    */
    commandMsg.ComMode = 4;
    commandMsg.IsStart = false;
    dt_message_package::CloudMessage pubMsg;
    pubMsg.TimeStamp = ros::Time::now().toNSec();
    pubMsg.SourceID = Gloal_Server_0;
    pubMsg.TargetID = _objectID;
    pubMsg.MessageID = UavCommandID;
    pubMsg.MessageData = x2struct::X::tojson(commandMsg);
    _networkMsgPub.publish(pubMsg);
}
