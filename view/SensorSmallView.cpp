#include "SensorSmallView.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QString>
#include "../sensor/ObserverInterface.h"
#include <QMouseEvent>
#include <iostream>
namespace Sensor {
namespace View {

SmallSensorView::SmallSensorView(AbstractSensor& sensor, MainSensorView& main, QWidget* parent)
    : QFrame(parent), sensor(sensor) , name_label(new QLabel()), sensor_type_label(new QLabel()), short_description_label(new QLabel())
{
    setFrameShape(QFrame::StyledPanel);
    setMaximumSize(99999, 100);
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    layout->addWidget(name_label);
    layout->addWidget(sensor_type_label);
    layout->addWidget(short_description_label);
    
    connect(this, &Sensor::View::SmallSensorView::clickedWithSensor, &main, &Sensor::View::MainSensorView::update);    
    sensor.addObserver(this);
}

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
        delete this;
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
        std::cout << "clicked emitted" << std::endl;
    }
    QFrame::mousePressEvent(event);
}


}
}
