#include "MainWindow.h"
#include <iostream>
namespace Sensor
{
namespace View
{
    
MainWindow::MainWindow(Aside& aside, MainSensorView& main, SensorManager& manager, QWidget *parent) 
: QMainWindow(parent), aside(aside) ,main(main), manager(manager){    
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainWindowLayout = new QHBoxLayout(centralWidget);
    mainWindowLayout->addWidget(&aside);
    mainWindowLayout->addWidget(&main);
    setCentralWidget(centralWidget);
    show();
};

void MainWindow::changeMain(AbstractSensor* sensor){
    main.changeSensor(sensor);
};

MainWindow::~MainWindow() {
    delete &aside;
    delete &main;
    delete &manager;
};
} 
} 