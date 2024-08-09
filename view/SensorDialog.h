#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H

#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include "MainWindow.h"
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
#include <QtWidgets/QTableWidget>
#include "TableButtonItem.h"
#include <unordered_map>

namespace Sensor {
namespace View {

class SensorDialog: public QDialog {
    Q_OBJECT
  private:
    MainWindow& mainWindow;
    AbstractSensor* sensor;
    std::unordered_map<std::string, QLineEdit*> dataFields;

    QLineEdit  titleLE;
    QLineEdit  shortDescLE;
    QTextEdit  longDescTE;
    QLineEdit  sensibilityLE;
    QLineEdit  spanSimulLE;
    QComboBox* typeCB;
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

    QGridLayout* dataLayout;
    TableButtonItem* addP;
    QFrame dataOutFrame;
    QLabel  dataL;
    QTableWidgetItem* yAxisLabelItem;
    QTableWidget* tableWidget; 
    

    void addFrame(QString label, QWidget & widget, QLayout& layout);   
  
  public:
    SensorDialog(MainWindow& mainWinow, AbstractSensor* sensor = nullptr);
    
  private slots:
    void saveSensor();
    void showType(int index);
    void addPoint();
    void removeColumn();
};

}
}

#endif
