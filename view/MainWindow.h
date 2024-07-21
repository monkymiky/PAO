#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "Aside.h"
#include "MainSensorView.h"

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
    public:
    ~MainWindow() override;
    MainWindow(Aside& aside,MainSensorView& main,SensorManager& manager, QWidget *parent = nullptr);
    private slots:
    void changeMain(AbstractSensor* sensor);
};

} 
}

#endif