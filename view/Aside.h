#ifndef ASIDE_H
#define ASIDE_H

#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include "../sensor/SensorManager.h"
#include "SensorView.h"
#include "SensorSmallView.h"
#include "MainWindow.h"

#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>




namespace Sensor {
namespace View {
  class SmallSensorView;

class Aside: public QWidget , public ObserverInterface{
    Q_OBJECT
  private:
    std::list<SmallSensorView*> smallSViewList;
    QFrame* sensorOutFrame;
    QVBoxLayout* sensorsLayout; 
    QLineEdit* search;
  public:
    Aside(QWidget* parent = nullptr);
    void clearAllSSV();
    void deleteSSV(AbstractSensor* sensor);
    void addSSV(SmallSensorView* ssv);

  private slots:
    void searchSSV() const;

  
};

}
}

#endif
