#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H

#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include <vector>
#include <array>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/qdialog.h>
#include "sensorSmallView.h"
#include "../sensor/SensorManager.h"

namespace Sensor {
namespace View {

class SensorDialog: public QDialog {
    Q_OBJECT
  private:
    SensorManager* manager;

    std::vector<std::array<QLineEdit*, 2>> points;
    QGridLayout* dataLayout;
    QPushButton addP;

    QLineEdit  titleLE;
    QLineEdit  shortDescLE;
    QTextEdit  longDescTE;
    QLineEdit  sensibilityLE;
    QLineEdit  spanSimulLE;
    QComboBox  typeCB;
    QLineEdit  xAxisLE;
    QLineEdit  maxLE;
    QLineEdit  minLE;
    
    QLineEdit  dustA;
    QLineEdit  dustB;

    QLineEdit  humidA;
    QLineEdit  humidB;
    QLineEdit  humidC;

    QLineEdit  tempR0;
    QLineEdit  tempAlpha;
    QLineEdit  tempBeta;
    QLineEdit  tempGamma;
    QLineEdit  tempDelta;
    QLineEdit  tempEpsilon;
    QLineEdit  tempZeta;
    QFrame  tempFrame;
    QFrame  humidFrame;
    QFrame  dustFrame;

    

    void addFrame(QString label, QWidget & widget, QLayout& layout);
    void addPoint();
  
  public:
    SensorDialog(SensorManager* manager,QWidget* parent =  nullptr);
    ~SensorDialog();
  private slots:
    void closeDialog();
    void saveSensor();
    void showType(int index);
};

}
}

#endif
