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
    QLabel* name_label;
    QLabel* sensor_type_label;
    QLabel* short_description_label;
  protected:
    void mousePressEvent(QMouseEvent *event) override;

  public:
    SmallSensorView(AbstractSensor& sensor, MainWindow& mainWindow);
    ~SmallSensorView();
    void update(AbstractSensor* sensor) override;
    void endObservation() ;
    const AbstractSensor* getSensor() const;

  signals:
    void clickedWithSensor(AbstractSensor* sensor);
    
};

}
}

#endif
