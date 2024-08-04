#include "SensorSmallView.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QString>
#include "../sensor/ObserverInterface.h"
#include <QMouseEvent>
#include <iostream>
#include "Aside.h"

namespace Sensor {
namespace View {

SmallSensorView::SmallSensorView(AbstractSensor& sensor, MainWindow& mainWindow)
    : QFrame(&mainWindow),
    sensor(sensor) ,
    mainWindow(mainWindow),
    name_label(new QLabel()), sensor_type_label(new QLabel()), short_description_label(new QLabel())
{   
    setFrameShape(QFrame::StyledPanel);
    setMaximumSize(99999, 100);
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    layout->addWidget(name_label);
    layout->addWidget(sensor_type_label);
    layout->addWidget(short_description_label);

    connect(this, SIGNAL(clickedWithSensor(AbstractSensor*)), &mainWindow, SLOT(changeCurrentSensor(AbstractSensor*))); 
    sensor.addObserver(this);
}

SmallSensorView::~SmallSensorView(){
    sensor.removeObserver(this);
};

void SmallSensorView::show() {
    name_label->setText(QString::fromStdString(sensor.getName()));
    sensor_type_label->setText("Sensore: " + QString::fromStdString(sensor.getSensorType()));
    short_description_label->setText(QString::fromStdString(sensor.getShortDescription()));
}

void SmallSensorView::update(AbstractSensor* sensor) {
    if(sensor != nullptr){
        name_label->setText(QString::fromStdString(sensor->getName()));
        sensor_type_label->setText("Sensore: " + QString::fromStdString(sensor->getSensorType()));
        short_description_label->setText(QString::fromStdString(sensor->getShortDescription()));
    }else{
        std::cerr << "Sensor is nullptr in SmallSensorView::update" << std::endl;
    }
}
 void SmallSensorView::endObservation() {
        sensor.removeObserver(this);
 }

const AbstractSensor* SmallSensorView::getSensor() const
{
    return &sensor;
}

void SmallSensorView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clickedWithSensor(&sensor);
    }
    QFrame::mousePressEvent(event);
}


}
}
