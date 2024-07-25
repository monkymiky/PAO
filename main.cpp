#include "./view/Aside.h"
#include "./view/MainSensorView.h"
#include "./sensor/Dust25S.h"
#include "./sensor/AbstractSensor.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include "./view/MainWindow.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Sensor::SensorManager  manager =  Sensor::SensorManager();
    Sensor::View::MainSensorView  main =  Sensor::View::MainSensorView(manager);
    Sensor::View::Aside  aside =  Sensor::View::Aside(manager, main);
    // debug
    std::string prova = "prova";
    const float a = 10;
    const float b = 100;
    const float c = 0;
    const unsigned int d = 1;
    Sensor::Dust25S* dustSensor = new Sensor::Dust25S(prova,prova,prova,prova,d,a,b,c);
    manager.addSensor(dustSensor);
    // fine debug
    Sensor::View::MainWindow mainW =  Sensor::View::MainWindow(aside,main, manager);
    mainW.show();
    mainW.resize(1024, 512);


    return app.exec();
}

