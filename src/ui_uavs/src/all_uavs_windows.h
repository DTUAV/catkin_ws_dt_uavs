#ifndef ALL_UAVS_WINDOWS_H
#define ALL_UAVS_WINDOWS_H

#include <QWidget>
#include "uavs_main_window.h"
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
  std::shared_ptr<UAVInfoClass> info_ptr;

protected:
    void timerEvent(QTimerEvent *event);
public Q_SLOTS:
  void ui_update_timeout();
private:
  std::string packVector3(double x, double y, double z);
  void resetAllFlightMode();
  Ui::all_uavs_windows *ui;
};

#endif // ALL_UAVS_WINDOWS_H
