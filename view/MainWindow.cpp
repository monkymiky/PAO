#include "MainWindow.h"
#include "SensorDialog.h"
#include <iostream>
#include <QFileDialog>
#include "../sensor/JsonPharser.h"
#include <QMessageBox>

namespace Sensor
{namespace View
{
    
MainWindow::MainWindow( SensorManager& manager,Aside& aside , SensorView& sensorView, QWidget *parent  )
: QMainWindow(parent),  manager(manager) ,aside(aside) ,sensorView(sensorView){
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainWindowLayout = new QVBoxLayout(centralWidget);

    QFrame* topFrame = new QFrame(this);
    QHBoxLayout* topFrameLayout = new QHBoxLayout(topFrame);
    mainWindowLayout->addWidget(topFrame);

    QPushButton *buttonSave = new QPushButton("Salva", topFrame);
    QPushButton *buttonOpen = new QPushButton("Apri", topFrame);
    QPushButton *buttonClose = new QPushButton("Chiudi", topFrame);
    QPushButton *buttonSimulate = new QPushButton("Simula", topFrame);
    QPushButton *buttonModify = new QPushButton("Modifica", topFrame);
    QPushButton *buttonDelete = new QPushButton("Elimina", topFrame);
    topFrameLayout->addWidget(buttonSave);
    topFrameLayout->addWidget(buttonOpen);
    topFrameLayout->addWidget(buttonClose);
    topFrameLayout->addStretch();
    topFrameLayout->addWidget(buttonSimulate);
    topFrameLayout->addWidget(buttonModify);
    topFrameLayout->addWidget(buttonDelete);
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveSensors()));
    connect(buttonOpen, SIGNAL(clicked()), this, SLOT(openSensorFile()));
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(closeSensors()));
    connect(buttonSimulate, SIGNAL(clicked()), this, SLOT(simulate()));
    connect(buttonModify, SIGNAL(clicked()), this, SLOT(modify()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(deleteSensor()));

    QFrame* middleFrame = new QFrame(this);
    
    QHBoxLayout* middleFrameLayout = new QHBoxLayout(middleFrame);
    mainWindowLayout->addWidget(middleFrame);

    QFrame* asideFrame = new QFrame(this);
    asideFrame->setFixedWidth(300);
    QVBoxLayout* asideFrameLayout = new QVBoxLayout(asideFrame);
    asideFrameLayout->addWidget(&aside);
    
    QPushButton *buttonAdd = new QPushButton("Aggiungi", asideFrame);
    asideFrameLayout->addWidget(buttonAdd);
    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(buttonAddClicked()));
    middleFrameLayout->addWidget(asideFrame);

    middleFrameLayout->addWidget(&sensorView);
    setCentralWidget(centralWidget);
    show();
};

MainWindow::~MainWindow() {
    delete &aside;
    delete &sensorView;
    delete &manager;
};

void MainWindow::changeCurrentSensor(AbstractSensor* sensor){
    sensorView.changeSensor(sensor);
    currentSensor = sensor;
};

void MainWindow::addSensor(AbstractSensor* sensor){
    manager.addSensor(sensor);
    aside.addSSV(new SmallSensorView(*sensor, *this));
    changeCurrentSensor(sensor);
}


void MainWindow::buttonAddClicked(){
    SensorDialog* typeDialog = new SensorDialog(*this);
    typeDialog->exec();
};

void MainWindow::deleteSensor(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this, 
        "Elimina Sensore", 
        "Tutte le modifiche non salvate andranno perse. Sei sicuro di voler eliminare il sensore?",
        QMessageBox::Yes | QMessageBox::No
        );
    if (reply == QMessageBox::No) {
        return; 
    }
    manager.removeSensor(currentSensor);
    aside.deleteSSV(currentSensor);
    sensorView.changeSensor(nullptr);
    changeCurrentSensor(nullptr);
};

void MainWindow::saveSensors(){
    QString filename = QFileDialog::getSaveFileName(
        this, "Save sensors", QDir::homePath(), "Json files (*.json)");
    if(filename.isEmpty()){
        return;
    }
    Sensor::JsonPharser::savetoJson(manager, filename);
};

void MainWindow::openSensorFile(){
    QString filename = QFileDialog::getOpenFileName(
        this, "Open sensors", QDir::homePath(), "Json files (*.json)");
    if(filename.isEmpty()){
        return;
    }
    Sensor::JsonPharser::openfromJson(manager, aside, this, filename);
};

void MainWindow::closeSensors(){

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this, 
        "Chiudi Sensori", 
        "Tutte le modifiche non salvate andranno perse, compresi tutti i sensori aggiunti 
        dopo l'ultimo salvataggio.  Sei sicuro di voler chiudere il file ?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return; 
    }

    manager.cleanSensors();
    aside.clearAllSSV();
    sensorView.changeSensor(nullptr);
};

void MainWindow::simulate(){
    if(currentSensor == nullptr){
        return;
    }
    currentSensor->simulate();
}
void MainWindow::modify() {
    if(currentSensor == nullptr){
        return;
    }
    SensorDialog* typeDialog = new SensorDialog( *this ,currentSensor);
    typeDialog->exec();
};
} 
} 
