#include "uavs_main_window.h"
#include "ui_uavs_main_window.h"

uavs_main_window::uavs_main_window(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::uavs_main_window)
{
  ui->setupUi(this);
  m_nTimerID = this->startTimer(500);//500ms
  ros::NodeHandle n("~");
  std::string networkMsgSubName = "/Server1/Message_From_Cloud";
  n.getParam("NetworkMsgSubName",networkMsgSubName);
  std::string networkMsgPubName = "/Server1/Message_To_Cloud";
  n.getParam("NetworkMsgPubName",networkMsgPubName);

  _networkMsgSub = n.subscribe(networkMsgSubName,1,&uavs_main_window::network_msg_sub_cb,this);
  _networkMsgPub = n.advertise<dt_message_package::CloudMessage>(networkMsgPubName,1);



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
  QPalette pe;
  pe.setColor(QPalette::WindowText,Qt::white);
  ui->manual->setPalette(pe);
  ui->stabilizing->setPalette(pe);
  ui->altitude->setPalette(pe);
  ui->position->setPalette(pe);
  ui->offboard->setPalette(pe);
  ui->return_2->setPalette(pe);
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
  QPalette pe;
  pe.setColor(QPalette::WindowText,Qt::green);
  switch (info.FMode) {
  case 0:
    ui->manual->setPalette(pe);
    break;
  case 1:
    ui->stabilizing->setPalette(pe);
    break;
  case 2:
    ui->altitude->setPalette(pe);
    break;
  case 3:
    ui->position->setPalette(pe);
    break;
  case 4:
    ui->offboard->setPalette(pe);
    break;
  case 5:
    ui->return_2->setPalette(pe);
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
    pe.setColor(QPalette::WindowText,Qt::green);
    ui->is_connect->setPalette(pe);
  }
  else
  {
    pe.setColor(QPalette::WindowText,Qt::white);
    ui->is_connect->setPalette(pe);
  }
  if(info.IsArm)
  {
    pe.setColor(QPalette::WindowText,Qt::green);
    ui->is_arm->setPalette(pe);
  }
  else
  {
    pe.setColor(QPalette::WindowText,Qt::white);
    ui->is_arm->setPalette(pe);
  }
  ui->voltage->setText(QString::fromLocal8Bit(std::to_string(info.Voltage).data()));
  ui->remaining->setText(QString::fromLocal8Bit(std::to_string(info.Remaining).data()));
}

void uavs_main_window::ui_update_timeout()
{
  switch (_objectID) {
  case 1:
    updateUi(_uav1Info);
    break;
  case 2:
    updateUi(_uav2Info);
    break;
  case 3:
    updateUi(_uav3Info);
    break;
  case 4:
    updateUi(_uav4Info);
    break;
  case 5:
    updateUi(_uav5Info);
    break;
  case 6:
    updateUi(_uav6Info);
    break;
  case 7:
    updateUi(_uav7Info);
    break;
  case 8:
    updateUi(_uav8Info);
    break;
  case 9:
    updateUi(_uav9Info);
    break;
  case 10:
    updateUi(_uav10Info);
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
      switch (msg.get()->SourceID) {
      case 1:
      {
        _uav1Info = uavInfoMsg;
      }
        break;
      case 2:
      {
        _uav2Info = uavInfoMsg;
      }
        break;
      case 3:
      {
        _uav3Info = uavInfoMsg;
      }
        break;
      case 4:
      {
        _uav4Info = uavInfoMsg;
      }
        break;
      case 5:
      {
        _uav5Info = uavInfoMsg;
      }
        break;
      case 6:
      {
        _uav6Info = uavInfoMsg;
      }
        break;
      case 7:
      {
        _uav7Info = uavInfoMsg;
      }
        break;
      case 8:
      {
        _uav8Info = uavInfoMsg;
      }
        break;
      case 9:
      {
        _uav9Info = uavInfoMsg;
      }
        break;
      case 10:
      {
        _uav10Info = uavInfoMsg;
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
}

void uavs_main_window::on_pb_uav2_clicked()
{
  _objectID = 2;
}

void uavs_main_window::on_pb_uav3_clicked()
{
  _objectID = 3;
}

void uavs_main_window::on_pb_uav4_clicked()
{
  _objectID = 4;
}

void uavs_main_window::on_pb_uav5_clicked()
{
  _objectID = 5;
}

void uavs_main_window::on_pb_uav6_clicked()
{
  _objectID = 6;
}

void uavs_main_window::on_pb_uav7_clicked()
{
  _objectID = 7;
}

void uavs_main_window::on_pb_uav8_clicked()
{
  _objectID = 8;
}

void uavs_main_window::on_pb_uav9_clicked()
{
  _objectID = 9;
}

void uavs_main_window::on_pb_uav10_clicked()
{
  _objectID = 10;
}

void uavs_main_window::on_pb_uavall_clicked()
{

}

void uavs_main_window::on_pb_is_start_clicked()
{

}

void uavs_main_window::on_pb_is_arm_clicked()
{

}

void uavs_main_window::on_pb_is_position_mode_clicked()
{

}

void uavs_main_window::on_pb_is_offboard_mode_clicked()
{

}

void uavs_main_window::on_pb_target_pos_ok_clicked()
{

}

void uavs_main_window::on_pb_target_vel_ok_clicked()
{

}
