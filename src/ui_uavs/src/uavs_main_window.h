#ifndef UAVS_MAIN_WINDOW_H
#define UAVS_MAIN_WINDOW_H

#include <QWidget>
#include <QTimer>
#include "iostream"
#include "ros/ros.h"
#include "dt_message_package/CloudMessage.h"
#include "dt_common/define_common.h"
#include <string>
#include "tf/tf.h"
#include "all_uavs_windows.h"
#include "ui_uavs_main_window.h"
#include "memory"
using namespace DTUAV;
class UAVInfoClass
{
public:
  UAVInfoClass()
  {
    _uav1Info.AVelX = 0;
    _uav1Info.AVelY = 0;
    _uav1Info.AVelZ = 0;
    _uav1Info.FMode = 0;
    _uav1Info.IsArm = false;
    _uav1Info.LVelX = 0;
    _uav1Info.LVelY = 0;
    _uav1Info.LVelZ = 0;
    _uav1Info.NetPx4 = false;
    _uav1Info.PosX = 0;
    _uav1Info.PosY = 0;
    _uav1Info.PosZ = 0;
    _uav1Info.Remaining = 0;
    _uav1Info.Voltage = 0;
    _uav1Info.RotX = 0;
    _uav1Info.RotY = 0;
    _uav1Info.RotZ = 0;
    _uav1Info.RotW = 1;

    _uav2Info.AVelX = 0;
    _uav2Info.AVelY = 0;
    _uav2Info.AVelZ = 0;
    _uav2Info.FMode = 0;
    _uav2Info.IsArm = false;
    _uav2Info.LVelX = 0;
    _uav2Info.LVelY = 0;
    _uav2Info.LVelZ = 0;
    _uav2Info.NetPx4 = false;
    _uav2Info.PosX = 0;
    _uav2Info.PosY = 0;
    _uav2Info.PosZ = 0;
    _uav2Info.Remaining = 0;
    _uav2Info.Voltage = 0;
    _uav2Info.RotX = 0;
    _uav2Info.RotY = 0;
    _uav2Info.RotZ = 0;
    _uav2Info.RotW = 1;

    _uav3Info.AVelX = 0;
    _uav3Info.AVelY = 0;
    _uav3Info.AVelZ = 0;
    _uav3Info.FMode = 0;
    _uav3Info.IsArm = false;
    _uav3Info.LVelX = 0;
    _uav3Info.LVelY = 0;
    _uav3Info.LVelZ = 0;
    _uav3Info.NetPx4 = false;
    _uav3Info.PosX = 0;
    _uav3Info.PosY = 0;
    _uav3Info.PosZ = 0;
    _uav3Info.Remaining = 0;
    _uav3Info.Voltage = 0;
    _uav3Info.RotX = 0;
    _uav3Info.RotY = 0;
    _uav3Info.RotZ = 0;
    _uav3Info.RotW = 1;

    _uav4Info.AVelX = 0;
    _uav4Info.AVelY = 0;
    _uav4Info.AVelZ = 0;
    _uav4Info.FMode = 0;
    _uav4Info.IsArm = false;
    _uav4Info.LVelX = 0;
    _uav4Info.LVelY = 0;
    _uav4Info.LVelZ = 0;
    _uav4Info.NetPx4 = false;
    _uav4Info.PosX = 0;
    _uav4Info.PosY = 0;
    _uav4Info.PosZ = 0;
    _uav4Info.Remaining = 0;
    _uav4Info.Voltage = 0;
    _uav4Info.RotX = 0;
    _uav4Info.RotY = 0;
    _uav4Info.RotZ = 0;
    _uav4Info.RotW = 1;


    _uav5Info.AVelX = 0;
    _uav5Info.AVelY = 0;
    _uav5Info.AVelZ = 0;
    _uav5Info.FMode = 0;
    _uav5Info.IsArm = false;
    _uav5Info.LVelX = 0;
    _uav5Info.LVelY = 0;
    _uav5Info.LVelZ = 0;
    _uav5Info.NetPx4 = false;
    _uav5Info.PosX = 0;
    _uav5Info.PosY = 0;
    _uav5Info.PosZ = 0;
    _uav5Info.Remaining = 0;
    _uav5Info.Voltage = 0;
    _uav5Info.RotX = 0;
    _uav5Info.RotY = 0;
    _uav5Info.RotZ = 0;
    _uav5Info.RotW = 1;


    _uav6Info.AVelX = 0;
    _uav6Info.AVelY = 0;
    _uav6Info.AVelZ = 0;
    _uav6Info.FMode = 0;
    _uav6Info.IsArm = false;
    _uav6Info.LVelX = 0;
    _uav6Info.LVelY = 0;
    _uav6Info.LVelZ = 0;
    _uav6Info.NetPx4 = false;
    _uav6Info.PosX = 0;
    _uav6Info.PosY = 0;
    _uav6Info.PosZ = 0;
    _uav6Info.Remaining = 0;
    _uav6Info.Voltage = 0;
    _uav6Info.RotX = 0;
    _uav6Info.RotY = 0;
    _uav6Info.RotZ = 0;
    _uav6Info.RotW = 1;


    _uav7Info.AVelX = 0;
    _uav7Info.AVelY = 0;
    _uav7Info.AVelZ = 0;
    _uav7Info.FMode = 0;
    _uav7Info.IsArm = false;
    _uav7Info.LVelX = 0;
    _uav7Info.LVelY = 0;
    _uav7Info.LVelZ = 0;
    _uav7Info.NetPx4 = false;
    _uav7Info.PosX = 0;
    _uav7Info.PosY = 0;
    _uav7Info.PosZ = 0;
    _uav7Info.Remaining = 0;
    _uav7Info.Voltage = 0;
    _uav7Info.RotX = 0;
    _uav7Info.RotY = 0;
    _uav7Info.RotZ = 0;
    _uav7Info.RotW = 1;


    _uav8Info.AVelX = 0;
    _uav8Info.AVelY = 0;
    _uav8Info.AVelZ = 0;
    _uav8Info.FMode = 0;
    _uav8Info.IsArm = false;
    _uav8Info.LVelX = 0;
    _uav8Info.LVelY = 0;
    _uav8Info.LVelZ = 0;
    _uav8Info.NetPx4 = false;
    _uav8Info.PosX = 0;
    _uav8Info.PosY = 0;
    _uav8Info.PosZ = 0;
    _uav8Info.Remaining = 0;
    _uav8Info.Voltage = 0;
    _uav8Info.RotX = 0;
    _uav8Info.RotY = 0;
    _uav8Info.RotZ = 0;
    _uav8Info.RotW = 1;


    _uav9Info.AVelX = 0;
    _uav9Info.AVelY = 0;
    _uav9Info.AVelZ = 0;
    _uav9Info.FMode = 0;
    _uav9Info.IsArm = false;
    _uav9Info.LVelX = 0;
    _uav9Info.LVelY = 0;
    _uav9Info.LVelZ = 0;
    _uav9Info.NetPx4 = false;
    _uav9Info.PosX = 0;
    _uav9Info.PosY = 0;
    _uav9Info.PosZ = 0;
    _uav9Info.Remaining = 0;
    _uav9Info.Voltage = 0;
    _uav9Info.RotX = 0;
    _uav9Info.RotY = 0;
    _uav9Info.RotZ = 0;
    _uav9Info.RotW = 1;
    _uav10Info.AVelX = 0;
    _uav10Info.AVelY = 0;
    _uav10Info.AVelZ = 0;
    _uav10Info.FMode = 0;
    _uav10Info.IsArm = false;
    _uav10Info.LVelX = 0;
    _uav10Info.LVelY = 0;
    _uav10Info.LVelZ = 0;
    _uav10Info.NetPx4 = false;
    _uav10Info.PosX = 0;
    _uav10Info.PosY = 0;
    _uav10Info.PosZ = 0;
    _uav10Info.Remaining = 0;
    _uav10Info.Voltage = 0;
    _uav10Info.RotX = 0;
    _uav10Info.RotY = 0;
    _uav10Info.RotZ = 0;
    _uav10Info.RotW = 1;
  }
  UavInfo _uav1Info;
  UavInfo _uav2Info;
  UavInfo _uav3Info;
  UavInfo _uav4Info;
  UavInfo _uav5Info;
  UavInfo _uav6Info;
  UavInfo _uav7Info;
  UavInfo _uav8Info;
  UavInfo _uav9Info;
  UavInfo _uav10Info;

};
namespace Ui {
class uavs_main_window;
}

class uavs_main_window : public QWidget
{
  Q_OBJECT

public:
  explicit uavs_main_window(QWidget *parent = 0);
  ~uavs_main_window();
  int m_nTimerID;
  void network_msg_sub_cb(const dt_message_package::CloudMessageConstPtr& msg);
  //friend class all_uavs_windows;
  shared_ptr<UAVInfoClass> uav_info_class_ptr;
  UAVInfoClass all_info;


protected:
    void timerEvent(QTimerEvent *event);
public Q_SLOTS:
  void ui_update_timeout();
private Q_SLOTS:
  void on_pb_uav1_clicked();

  void on_pb_uav2_clicked();

  void on_pb_uav3_clicked();

  void on_pb_uav4_clicked();

  void on_pb_uav5_clicked();

  void on_pb_uav6_clicked();

  void on_pb_uav7_clicked();

  void on_pb_uav8_clicked();

  void on_pb_uav9_clicked();

  void on_pb_uav10_clicked();

  void on_pb_uavall_clicked();

  void on_pb_is_start_clicked();

  void on_pb_is_arm_clicked();

  void on_pb_is_position_mode_clicked();

  void on_pb_is_offboard_mode_clicked();

  void on_pb_target_pos_ok_clicked();

  void on_pb_target_vel_ok_clicked();

  void on_pb_is_stop_clicked();

private:

  void updateUi(const UavInfo& info);
  void resetAllFlightMode();
  void resetAllSelectBt();
  std::string packVector3(double x, double y, double z);

  int _objectID;//The current object id: 1,2,3,4,5,6,7,8,9,10-->UAV1,UAV2,UAV3,UAV4,....

  ros::Subscriber _networkMsgSub;
  ros::Publisher _networkMsgPub;

  Ui::uavs_main_window *ui;
};

#endif // UAVS_MAIN_WINDOW_H
