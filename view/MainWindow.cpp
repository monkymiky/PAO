#include "MainWindow.h"
#include <iostream>
#include <QFileDialog>
#include "JsonPharser.h"

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

void MainWindow::saveSensors(){
    QString filename = QFileDialog::getSaveFileName(this, "Save sensors", QDir::homePath(), "Json files (*.json)");
    if(filename.isEmpty()){
        return;
    }
    Sensor::JsonPharser::savetoJson(manager, filename);
};

void MainWindow::openSensorFile(){
    QString filename = QFileDialog::getOpenFileName(this, "Open sensors", QDir::homePath(), "Json files (*.json)");
    if(filename.isEmpty()){
        return;
    }
    Sensor::JsonPharser::openfromJson(manager, filename);
};

void MainWindow::closeSensors(){
    manager.clear();
};


} 
} 