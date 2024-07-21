#ifndef MAINSENSORVIEW_H
#define MAINSENSORVIEW_H

#include "../sensor/AbstractSensor.h"
#include "../sensor/ObserverInterface.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

namespace Sensor {
namespace View {

class MainSensorView: public QWidget, public ObserverInterface {
    Q_OBJECT
  private:
    AbstractSensor* sensor;
    QLabel *title;
    QLabel *type;
    QLabel *sensibility;
    QLabel *min;
    QLabel *max;
    QLabel *mean;
    QLabel *variance;
    QLineSeries *series;
    QChart *chart;
    QChartView* chartView;
    QLabel *longDesc;
  public:
    MainSensorView(AbstractSensor* sensor, QWidget* parent = nullptr);
    MainSensorView(QWidget* parent = nullptr);
    ~MainSensorView();
    void update(AbstractSensor* sensor = nullptr) override;
    void changeSensor(AbstractSensor* sensorPointer);

  private slots:
    void openSensorDialog();
    void deleteSensor();
    void simulate();
};

}
}

#endif