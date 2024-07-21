#ifndef ASIDE_H
#define ASIDE_H

#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "../sensor/SensorManager.h"
#include "MainSensorView.h"
#include "SensorSmallView.h"


namespace Sensor {
namespace View {

class Aside: public QWidget, public ObserverInterface {
    Q_OBJECT
  private:
    SensorManager& manager;
    std::vector<SmallSensorView*> sensorSViewList;
    QFrame* sensorScrollFrame;
    QVBoxLayout* SensorListLayout;
    MainSensorView& main; 
  public:
    Aside(SensorManager& manager,MainSensorView& main, QWidget* parent = nullptr);
    void show();
    void update(AbstractSensor* sensor) override;
  
  private slots:
    void addNewSensorClicked();
  
};

}
}

#endif