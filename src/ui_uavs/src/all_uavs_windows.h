#ifndef ALL_UAVS_WINDOWS_H
#define ALL_UAVS_WINDOWS_H

#include <QWidget>
#include "uavs_main_window.h"
#include <QLabel>
class UAVInfoClass;
namespace Ui {
class all_uavs_windows;
}
class all_uavs_windows : public QWidget
{
  Q_OBJECT

public:
  explicit all_uavs_windows(QWidget *parent = 0);
  ~all_uavs_windows();
  int m_nTimerID;
  std::shared_ptr<UAVInfoClass> info_ptr = NULL;
  std::shared_ptr<ros::Publisher> network_pub_ptr= NULL;

protected:
    void timerEvent(QTimerEvent *event);
public Q_SLOTS:
  void ui_update_timeout();
private Q_SLOTS:
  void on_pb_is_arm_clicked();

  void on_pb_is_start_clicked();

  void on_pb_is_offboard_mode_clicked();

  void on_pb_is_position_mode_clicked();

  void on_pb_is_stop_clicked();

private:
  std::string packVector3(double x, double y, double z);
  void updateFlightMode(int mode, QLabel *manual, QLabel *stabilizing, QLabel *altitude, QLabel *position, QLabel *offboard, QLabel *reture_val);
  void updateStatue(bool status, QLabel* qlb);

  void resetAllFlightMode();
  Ui::all_uavs_windows *ui;
};

#endif // ALL_UAVS_WINDOWS_H
