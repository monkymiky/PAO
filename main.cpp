#include "./view/MainWindow.h"
#include "./view/Aside.h"
#include "./view/MainSensorView.h"
#include "./sensor/AbstractSensor.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>

#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);



    Sensor::SensorManager  manager =  Sensor::SensorManager();
    Sensor::View::MainSensorView  mainView =  Sensor::View::MainSensorView();
    Sensor::View::Aside  aside =   Sensor::View::Aside();
    Sensor::View::MainWindow mainWindow =  Sensor::View::MainWindow(manager,aside,mainView);


    mainWindow.show();
    mainWindow.resize(1024, 512);


    return app.exec();
}

