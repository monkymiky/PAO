#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "Aside.h"
#include "SensorView.h"
#include "../sensor/SensorManager.h"
#include "../sensor/AbstractSensor.h"


namespace Sensor{
namespace View{
class Aside;
    
class MainWindow : public QMainWindow, public ObserverInterface {
    Q_OBJECT
    private:
    SensorManager& manager;
    Aside& aside;
    SensorView& sensorView;
    AbstractSensor* currentSensor;
    public:
    MainWindow( SensorManager& manager, 
                Aside& aside , 
                SensorView& sensorView,
                QWidget *parent = nullptr );
    void deleteCurrentSensor();
    void update(AbstractSensor* sensor) override;
 
    private slots:
    void changeCurrentSensor(AbstractSensor* sensor);
    void buttonAddClicked() ;
    void buttonDeleteClicked();
    void saveSensors() ;
    void openSensorFile() ;
    void closeSensors() ;
    void simulate() const;
    void modify() ;
};

} 
}

#endif
