#include "all_uavs_windows.h"
#include "ui_all_uavs_windows.h"

all_uavs_windows::all_uavs_windows(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::all_uavs_windows)
{
  ui->setupUi(this);
  m_nTimerID = this->startTimer(500);//500ms
}

std::string all_uavs_windows::packVector3(double x, double y, double z)
{
  std::string ret = "( "+ std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")";
  return ret;
}
void all_uavs_windows::timerEvent(QTimerEvent *event)
{
  if(event->timerId() == m_nTimerID){
    ui_update_timeout();
  }
}

void all_uavs_windows::updateFlightMode(int mode, QLabel* manual, QLabel* stabilizing, QLabel* altitude, QLabel* position, QLabel* offboard, QLabel* return_val)
{
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::green);
  switch (mode) {
  case 0:
    manual->setPalette(palette);
    break;
  case 1:
    stabilizing->setPalette(palette);
    break;
  case 2:
    altitude->setPalette(palette);
    break;
  case 3:
    position->setPalette(palette);
    break;
  case 4:
    offboard->setPalette(palette);
    break;
  case 5:
    return_val->setPalette(palette);
    break;
  default:
    break;
  }
}

void all_uavs_windows::updateStatue(bool status, QLabel *qlb)
{
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::green);
  if(status)
  {
    palette.setColor(QPalette::Background, Qt::green);
    qlb->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    qlb->setPalette(palette);
  }
}

void all_uavs_windows::resetAllFlightMode()
{
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::white);
  ui->uav1_manual->setAutoFillBackground(true);
  ui->uav1_manual->setPalette(palette);

  ui->uav1_stabilizing->setAutoFillBackground(true);
  ui->uav1_stabilizing->setPalette(palette);

  ui->uav1_altitude->setAutoFillBackground(true);
  ui->uav1_altitude->setPalette(palette);

  ui->uav1_position->setAutoFillBackground(true);
  ui->uav1_position->setPalette(palette);

  ui->uav1_offboard->setAutoFillBackground(true);
  ui->uav1_offboard->setPalette(palette);

  ui->uav1_return->setAutoFillBackground(true);
  ui->uav1_return->setPalette(palette);

  ui->uav2_manual->setAutoFillBackground(true);
  ui->uav2_manual->setPalette(palette);

  ui->uav2_stabilizing->setAutoFillBackground(true);
  ui->uav2_stabilizing->setPalette(palette);

  ui->uav2_altitude->setAutoFillBackground(true);
  ui->uav2_altitude->setPalette(palette);

  ui->uav2_position->setAutoFillBackground(true);
  ui->uav2_position->setPalette(palette);

  ui->uav2_offboard->setAutoFillBackground(true);
  ui->uav2_offboard->setPalette(palette);

  ui->uav2_return->setAutoFillBackground(true);
  ui->uav2_return->setPalette(palette);


  ui->uav3_manual->setAutoFillBackground(true);
  ui->uav3_manual->setPalette(palette);

  ui->uav3_stabilizing->setAutoFillBackground(true);
  ui->uav3_stabilizing->setPalette(palette);

  ui->uav3_altitude->setAutoFillBackground(true);
  ui->uav3_altitude->setPalette(palette);

  ui->uav3_position->setAutoFillBackground(true);
  ui->uav3_position->setPalette(palette);

  ui->uav3_offboard->setAutoFillBackground(true);
  ui->uav3_offboard->setPalette(palette);

  ui->uav3_return->setAutoFillBackground(true);
  ui->uav3_return->setPalette(palette);


  ui->uav4_manual->setAutoFillBackground(true);
  ui->uav4_manual->setPalette(palette);

  ui->uav4_stabilizing->setAutoFillBackground(true);
  ui->uav4_stabilizing->setPalette(palette);

  ui->uav4_altitude->setAutoFillBackground(true);
  ui->uav4_altitude->setPalette(palette);

  ui->uav4_position->setAutoFillBackground(true);
  ui->uav4_position->setPalette(palette);

  ui->uav4_offboard->setAutoFillBackground(true);
  ui->uav4_offboard->setPalette(palette);

  ui->uav4_return->setAutoFillBackground(true);
  ui->uav4_return->setPalette(palette);

  ui->uav5_manual->setAutoFillBackground(true);
  ui->uav5_manual->setPalette(palette);

  ui->uav5_stabilizing->setAutoFillBackground(true);
  ui->uav5_stabilizing->setPalette(palette);

  ui->uav5_altitude->setAutoFillBackground(true);
  ui->uav5_altitude->setPalette(palette);

  ui->uav5_position->setAutoFillBackground(true);
  ui->uav5_position->setPalette(palette);

  ui->uav5_offboard->setAutoFillBackground(true);
  ui->uav5_offboard->setPalette(palette);

  ui->uav5_return->setAutoFillBackground(true);
  ui->uav5_return->setPalette(palette);


  ui->uav6_manual->setAutoFillBackground(true);
  ui->uav6_manual->setPalette(palette);

  ui->uav6_stabilizing->setAutoFillBackground(true);
  ui->uav6_stabilizing->setPalette(palette);

  ui->uav6_altitude->setAutoFillBackground(true);
  ui->uav6_altitude->setPalette(palette);

  ui->uav6_position->setAutoFillBackground(true);
  ui->uav6_position->setPalette(palette);

  ui->uav6_offboard->setAutoFillBackground(true);
  ui->uav6_offboard->setPalette(palette);

  ui->uav6_return->setAutoFillBackground(true);
  ui->uav6_return->setPalette(palette);

  ui->uav7_manual->setAutoFillBackground(true);
  ui->uav7_manual->setPalette(palette);

  ui->uav7_stabilizing->setAutoFillBackground(true);
  ui->uav7_stabilizing->setPalette(palette);

  ui->uav7_altitude->setAutoFillBackground(true);
  ui->uav7_altitude->setPalette(palette);

  ui->uav7_position->setAutoFillBackground(true);
  ui->uav7_position->setPalette(palette);

  ui->uav7_offboard->setAutoFillBackground(true);
  ui->uav7_offboard->setPalette(palette);

  ui->uav7_return->setAutoFillBackground(true);
  ui->uav7_return->setPalette(palette);


  ui->uav8_manual->setAutoFillBackground(true);
  ui->uav8_manual->setPalette(palette);

  ui->uav8_stabilizing->setAutoFillBackground(true);
  ui->uav8_stabilizing->setPalette(palette);

  ui->uav8_altitude->setAutoFillBackground(true);
  ui->uav8_altitude->setPalette(palette);

  ui->uav8_position->setAutoFillBackground(true);
  ui->uav8_position->setPalette(palette);

  ui->uav8_offboard->setAutoFillBackground(true);
  ui->uav8_offboard->setPalette(palette);

  ui->uav8_return->setAutoFillBackground(true);
  ui->uav8_return->setPalette(palette);

  ui->uav9_manual->setAutoFillBackground(true);
  ui->uav9_manual->setPalette(palette);

  ui->uav9_stabilizing->setAutoFillBackground(true);
  ui->uav9_stabilizing->setPalette(palette);

  ui->uav9_altitude->setAutoFillBackground(true);
  ui->uav9_altitude->setPalette(palette);

  ui->uav9_position->setAutoFillBackground(true);
  ui->uav9_position->setPalette(palette);

  ui->uav9_offboard->setAutoFillBackground(true);
  ui->uav9_offboard->setPalette(palette);

  ui->uav9_return->setAutoFillBackground(true);
  ui->uav9_return->setPalette(palette);

  ui->uav10_manual->setAutoFillBackground(true);
  ui->uav10_manual->setPalette(palette);

  ui->uav10_stabilizing->setAutoFillBackground(true);
  ui->uav10_stabilizing->setPalette(palette);

  ui->uav10_altitude->setAutoFillBackground(true);
  ui->uav10_altitude->setPalette(palette);

  ui->uav10_position->setAutoFillBackground(true);
  ui->uav10_position->setPalette(palette);

  ui->uav10_offboard->setAutoFillBackground(true);
  ui->uav10_offboard->setPalette(palette);

  ui->uav10_return->setAutoFillBackground(true);
  ui->uav10_return->setPalette(palette);


}
void all_uavs_windows::ui_update_timeout()
{
  //std::cout<<"ddddd"<<std::endl;
  resetAllFlightMode();
  //std::cout<<"ddddd"<<std::endl;
  updateFlightMode(info_ptr.get()->_uav1Info.FMode,ui->uav1_manual,ui->uav1_stabilizing,ui->uav1_altitude,ui->uav1_position,ui->uav1_offboard,ui->uav1_return);
  updateFlightMode(info_ptr.get()->_uav2Info.FMode,ui->uav2_manual,ui->uav2_stabilizing,ui->uav2_altitude,ui->uav2_position,ui->uav2_offboard,ui->uav2_return);
  updateFlightMode(info_ptr.get()->_uav3Info.FMode,ui->uav3_manual,ui->uav3_stabilizing,ui->uav3_altitude,ui->uav3_position,ui->uav3_offboard,ui->uav3_return);
  updateFlightMode(info_ptr.get()->_uav4Info.FMode,ui->uav4_manual,ui->uav4_stabilizing,ui->uav4_altitude,ui->uav4_position,ui->uav4_offboard,ui->uav4_return);
  updateFlightMode(info_ptr.get()->_uav5Info.FMode,ui->uav5_manual,ui->uav5_stabilizing,ui->uav5_altitude,ui->uav5_position,ui->uav5_offboard,ui->uav5_return);
  updateFlightMode(info_ptr.get()->_uav6Info.FMode,ui->uav6_manual,ui->uav6_stabilizing,ui->uav6_altitude,ui->uav6_position,ui->uav6_offboard,ui->uav6_return);
  updateFlightMode(info_ptr.get()->_uav7Info.FMode,ui->uav7_manual,ui->uav7_stabilizing,ui->uav7_altitude,ui->uav7_position,ui->uav7_offboard,ui->uav7_return);
  updateFlightMode(info_ptr.get()->_uav8Info.FMode,ui->uav8_manual,ui->uav8_stabilizing,ui->uav8_altitude,ui->uav8_position,ui->uav8_offboard,ui->uav8_return);
  updateFlightMode(info_ptr.get()->_uav9Info.FMode,ui->uav9_manual,ui->uav9_stabilizing,ui->uav9_altitude,ui->uav9_position,ui->uav9_offboard,ui->uav9_return);
  updateFlightMode(info_ptr.get()->_uav10Info.FMode,ui->uav10_manual,ui->uav10_stabilizing,ui->uav10_altitude,ui->uav10_position,ui->uav10_offboard,ui->uav10_return);

  updateStatue(info_ptr.get()->_uav1Info.NetPx4,ui->uav1_is_connect);
  updateStatue(info_ptr.get()->_uav2Info.NetPx4,ui->uav2_is_connect);
  updateStatue(info_ptr.get()->_uav3Info.NetPx4,ui->uav3_is_connect);
  updateStatue(info_ptr.get()->_uav4Info.NetPx4,ui->uav4_is_connect);
  updateStatue(info_ptr.get()->_uav5Info.NetPx4,ui->uav5_is_connect);
  updateStatue(info_ptr.get()->_uav6Info.NetPx4,ui->uav6_is_connect);
  updateStatue(info_ptr.get()->_uav7Info.NetPx4,ui->uav7_is_connect);
  updateStatue(info_ptr.get()->_uav8Info.NetPx4,ui->uav8_is_connect);
  updateStatue(info_ptr.get()->_uav9Info.NetPx4,ui->uav9_is_connect);
  updateStatue(info_ptr.get()->_uav10Info.NetPx4,ui->uav10_is_connect);


  updateStatue(info_ptr.get()->_uav1Info.IsArm,ui->uav1_is_arm);
  updateStatue(info_ptr.get()->_uav2Info.IsArm,ui->uav2_is_arm);
  updateStatue(info_ptr.get()->_uav3Info.IsArm,ui->uav3_is_arm);
  updateStatue(info_ptr.get()->_uav4Info.IsArm,ui->uav4_is_arm);
  updateStatue(info_ptr.get()->_uav5Info.IsArm,ui->uav5_is_arm);
  updateStatue(info_ptr.get()->_uav6Info.IsArm,ui->uav6_is_arm);
  updateStatue(info_ptr.get()->_uav7Info.IsArm,ui->uav7_is_arm);
  updateStatue(info_ptr.get()->_uav8Info.IsArm,ui->uav8_is_arm);
  updateStatue(info_ptr.get()->_uav9Info.IsArm,ui->uav9_is_arm);
  updateStatue(info_ptr.get()->_uav10Info.IsArm,ui->uav10_is_arm);

  updateStatue(info_ptr.get()->_uav1Info.IsStart,ui->uav1_is_start);
  updateStatue(info_ptr.get()->_uav2Info.IsStart,ui->uav2_is_start);
  updateStatue(info_ptr.get()->_uav3Info.IsStart,ui->uav3_is_start);
  updateStatue(info_ptr.get()->_uav4Info.IsStart,ui->uav4_is_start);
  updateStatue(info_ptr.get()->_uav5Info.IsStart,ui->uav5_is_start);
  updateStatue(info_ptr.get()->_uav6Info.IsStart,ui->uav6_is_start);
  updateStatue(info_ptr.get()->_uav7Info.IsStart,ui->uav7_is_start);
  updateStatue(info_ptr.get()->_uav8Info.IsStart,ui->uav8_is_start);
  updateStatue(info_ptr.get()->_uav9Info.IsStart,ui->uav9_is_start);
  updateStatue(info_ptr.get()->_uav10Info.IsStart,ui->uav10_is_start);
//std::cout<<"ddddd"<<std::endl;
  updateStatue(info_ptr.get()->_uavLinkStatus.at(0),ui->uav1_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(1),ui->uav2_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(2),ui->uav3_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(3),ui->uav4_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(4),ui->uav5_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(5),ui->uav6_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(6),ui->uav7_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(7),ui->uav8_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(8),ui->uav9_is_link);
  updateStatue(info_ptr.get()->_uavLinkStatus.at(9),ui->uav10_is_link);

  ui->pb_is_stop->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_start->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_arm->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_offboard_mode->setStyleSheet("background-color: rgb(255,255,255)");
  ui->pb_is_position_mode->setStyleSheet("background-color: rgb(255,255,255)");
//std::cout<<"ddddd"<<std::endl;
}

all_uavs_windows::~all_uavs_windows()
{
  this->killTimer(m_nTimerID);
  delete ui;
}

void all_uavs_windows::on_pb_is_arm_clicked()
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
  pubMsg.MessageID = UavCommandID;
  pubMsg.MessageData = x2struct::X::tojson(commandMsg);
  for(int i=1;i<=10;i++)
  {
    pubMsg.TargetID = i;
    network_pub_ptr.get()->publish(pubMsg);
  }
}

void all_uavs_windows::on_pb_is_start_clicked()
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
  pubMsg.MessageID = UavCommandID;
  pubMsg.MessageData = x2struct::X::tojson(commandMsg);
  for(int i=1;i<=10;i++)
  {
    pubMsg.TargetID = i;
    network_pub_ptr.get()->publish(pubMsg);
  }
}

void all_uavs_windows::on_pb_is_offboard_mode_clicked()
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
  pubMsg.MessageID = UavCommandID;
  pubMsg.MessageData = x2struct::X::tojson(commandMsg);
  for(int i=1;i<=10;i++)
  {
    pubMsg.TargetID = i;
    network_pub_ptr.get()->publish(pubMsg);
  }
}

void all_uavs_windows::on_pb_is_position_mode_clicked()
{
ui->pb_is_position_mode->setStyleSheet("background-color: rgb(0,255,0)");
}

void all_uavs_windows::on_pb_is_stop_clicked()
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
  pubMsg.MessageID = UavCommandID;
  pubMsg.MessageData = x2struct::X::tojson(commandMsg);
  for(int i=1;i<=10;i++)
  {
    pubMsg.TargetID = i;
    network_pub_ptr.get()->publish(pubMsg);
  }

}
