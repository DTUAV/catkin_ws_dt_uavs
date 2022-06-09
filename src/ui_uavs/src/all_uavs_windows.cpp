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
  resetAllFlightMode();
  QPalette palette;
  palette.setColor(QPalette::Background, Qt::green);
  switch (info_ptr.get()->_uav1Info.FMode) {
  case 0:
    ui->uav1_manual->setPalette(palette);
    break;
  case 1:
    ui->uav1_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav1_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav1_position->setPalette(palette);
    break;
  case 4:
    ui->uav1_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav1_return->setPalette(palette);
    break;
  default:
    break;
  }

  switch (info_ptr.get()->_uav2Info.FMode) {
  case 0:
    ui->uav2_manual->setPalette(palette);
    break;
  case 1:
    ui->uav2_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav2_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav2_position->setPalette(palette);
    break;
  case 4:
    ui->uav2_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav2_return->setPalette(palette);
    break;
  default:
    break;
  }

  switch (info_ptr.get()->_uav3Info.FMode) {
  case 0:
    ui->uav3_manual->setPalette(palette);
    break;
  case 1:
    ui->uav3_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav3_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav3_position->setPalette(palette);
    break;
  case 4:
    ui->uav3_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav3_return->setPalette(palette);
    break;
  default:
    break;
  }

  switch (info_ptr.get()->_uav4Info.FMode) {
  case 0:
    ui->uav4_manual->setPalette(palette);
    break;
  case 1:
    ui->uav4_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav4_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav4_position->setPalette(palette);
    break;
  case 4:
    ui->uav4_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav4_return->setPalette(palette);
    break;
  default:
    break;
  }

  switch (info_ptr.get()->_uav5Info.FMode) {
  case 0:
    ui->uav5_manual->setPalette(palette);
    break;
  case 1:
    ui->uav5_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav5_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav5_position->setPalette(palette);
    break;
  case 4:
    ui->uav5_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav5_return->setPalette(palette);
    break;
  default:
    break;
  }

  switch (info_ptr.get()->_uav6Info.FMode) {
  case 0:
    ui->uav6_manual->setPalette(palette);
    break;
  case 1:
    ui->uav6_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav6_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav6_position->setPalette(palette);
    break;
  case 4:
    ui->uav6_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav6_return->setPalette(palette);
    break;
  default:
    break;
  }
  switch (info_ptr.get()->_uav7Info.FMode) {
  case 0:
    ui->uav7_manual->setPalette(palette);
    break;
  case 1:
    ui->uav7_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav7_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav7_position->setPalette(palette);
    break;
  case 4:
    ui->uav7_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav7_return->setPalette(palette);
    break;
  default:
    break;
  }
  switch (info_ptr.get()->_uav8Info.FMode) {
  case 0:
    ui->uav8_manual->setPalette(palette);
    break;
  case 1:
    ui->uav8_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav8_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav8_position->setPalette(palette);
    break;
  case 4:
    ui->uav8_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav8_return->setPalette(palette);
    break;
  default:
    break;
  }
  switch (info_ptr.get()->_uav9Info.FMode) {
  case 0:
    ui->uav9_manual->setPalette(palette);
    break;
  case 1:
    ui->uav9_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav9_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav9_position->setPalette(palette);
    break;
  case 4:
    ui->uav9_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav9_return->setPalette(palette);
    break;
  default:
    break;
  }
  switch (info_ptr.get()->_uav10Info.FMode) {
  case 0:
    ui->uav10_manual->setPalette(palette);
    break;
  case 1:
    ui->uav10_stabilizing->setPalette(palette);
    break;
  case 2:
    ui->uav10_altitude->setPalette(palette);
    break;
  case 3:
    ui->uav10_position->setPalette(palette);
    break;
  case 4:
    ui->uav10_offboard->setPalette(palette);
    break;
  case 5:
    ui->uav10_return->setPalette(palette);
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
  if(info_ptr.get()->_uav1Info.NetPx4)
  {
    palette.setColor(QPalette::Background, Qt::green);
    ui->uav1_is_connect->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->uav1_is_connect->setPalette(palette);
  }



  if(info_ptr.get()->_uav1Info.IsArm)
  {
    palette.setColor(QPalette::Background,Qt::green);
    ui->uav1_is_arm->setPalette(palette);
  }
  else
  {
    palette.setColor(QPalette::Background,Qt::white);
    ui->uav1_is_arm->setPalette(palette);
  }

}

all_uavs_windows::~all_uavs_windows()
{
  this->killTimer(m_nTimerID);
  delete ui;
}
