#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "Aside.h"
#include "MainSensorView.h"
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
    MainSensorView& main;
    SensorManager& manager;
    AbstractSensor* currentSensor;
    public:
    ~MainWindow() override;
    MainWindow( SensorManager& manager, 
                Aside& aside , 
                MainSensorView& main,
                QWidget *parent = nullptr );
    void addNewSensor(AbstractSensor* sensor);
 
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
