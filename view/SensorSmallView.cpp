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

SmallSensorView::SmallSensorView(AbstractSensor& sensor, MainWindow& mainWindow):
    QFrame(&mainWindow),
    sensor(sensor) ,
    mainWindow(mainWindow),
    title(new QLabel(this)),
    sensorType(new QLabel(this)),
    short_description(new QLabel(this))
{   
    setFrameShape(QFrame::StyledPanel);
    setMaximumSize(99999, 100);
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    layout->addWidget(title);
    layout->addWidget(sensorType);
    layout->addWidget(short_description);

    title->setText(QString::fromStdString(sensor.getTitle()));
    sensorType->setText("Sensore: " + QString::fromStdString(sensor.getSensorType()));
    short_description->setText(QString::fromStdString(sensor.getShortDescription()));

    connect(this, SIGNAL(clickedWithSensor(AbstractSensor*)), &mainWindow, SLOT(changeCurrentSensor(AbstractSensor*))); 
    sensor.addObserver(this);
}

SmallSensorView::~SmallSensorView(){
    sensor.removeObserver(this);
};



void SmallSensorView::update(AbstractSensor* sensor) {
    if(sensor != nullptr){
        title->setText(QString::fromStdString(sensor->getTitle()));
        sensorType->setText("Sensore: " + QString::fromStdString(sensor->getSensorType()));
        short_description->setText(QString::fromStdString(sensor->getShortDescription()));
    }else{
        std::cerr << "Sensor is nullptr in SmallSensorView::update" << std::endl;
    }
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
