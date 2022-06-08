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
using namespace DTUAV;
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

private:

  void updateUi(const UavInfo& info);
  void resetAllFlightMode();
  std::string packVector3(double x, double y, double z);

  int _objectID;//The current object id: 1,2,3,4,5,6,7,8,9,10-->UAV1,UAV2,UAV3,UAV4,....

  ros::Subscriber _networkMsgSub;
  ros::Publisher _networkMsgPub;

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

  Ui::uavs_main_window *ui;
};

#endif // UAVS_MAIN_WINDOW_H
