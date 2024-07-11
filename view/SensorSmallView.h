#ifndef SENSOR_SMALL_VIEW_H
#define SENSOR_SMALL_VIEW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include <QtWidgets/QFrame>
#include "MainSensorView.h"

namespace Sensor {
namespace View {

class SmallSensorView: public QFrame, public ObserverInterface {
    Q_OBJECT
  private:
    AbstractSensor& sensor;
    QLabel* name_label;
    QLabel* sensor_type_label;
    QLabel* short_description_label;
  protected:
    void mousePressEvent(QMouseEvent *event) override;

  public:
    SmallSensorView(AbstractSensor& sensor, MainSensorView* main, QWidget* parent = nullptr);
    void show();
    void update(AbstractSensor* sensor) override;
  signals:
    void clicked();
};

}
}

#endif