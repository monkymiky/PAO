#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "Aside.h"
#include "SensorView.h"
#include "../sensor/SensorManager.h"
#include "../sensor/AbstractSensor.h"

class Aside;
namespace Sensor
{
namespace View
{
    
class MainWindow : public QMainWindow {
    Q_OBJECT
    private:
    Aside& aside;
    SensorView& sensorView;
    SensorManager& manager;
    AbstractSensor* currentSensor;
    public:
    ~MainWindow() override;
    MainWindow( SensorManager& manager, 
                Aside& aside , 
                SensorView& sensorView,
                QWidget *parent = nullptr );
    void addSensor(AbstractSensor* sensor);
 
    private slots:
    void changeCurrentSensor(AbstractSensor* sensor);
    void buttonAddClicked();
    void deleteSensor();
    void saveSensors();
    void openSensorFile();
    void closeSensors();
    void simulate();
    void modify();
};

} 
}

#endif
