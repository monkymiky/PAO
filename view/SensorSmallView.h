#ifndef SENSOR_SMALL_VIEW_H
#define SENSOR_SMALL_VIEW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include <QtWidgets/QFrame>
#include "MainWindow.h"



namespace Sensor {
namespace View {

class MainWindow;

class SmallSensorView: public QFrame, public ObserverInterface {
    Q_OBJECT
  private:
    AbstractSensor& sensor;
    MainWindow& mainWindow;
    QLabel* title;
    QLabel* sensorType;
    QLabel* short_description;
  protected:
    void mousePressEvent(QMouseEvent *event)  override;

  public:
    SmallSensorView(AbstractSensor& sensor, MainWindow& mainWindow);
    ~SmallSensorView();
    SmallSensorView(const SmallSensorView & SSV);
    SmallSensorView& operator= (const SmallSensorView& SSV) = delete;

    void update(AbstractSensor* sensor) override;
    const AbstractSensor* getSensor() const;

  signals:
    void clickedWithSensor(AbstractSensor* sensor);
    
};

}
}

#endif
