#include "SensorSmallView.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QString>
#include "../sensor/ObserverInterface.h"
#include <QMouseEvent>

namespace Sensor {
namespace View {

SmallSensorView::SmallSensorView(AbstractSensor& sensor, MainSensorView* main, QWidget* parent)
    : QFrame(parent), sensor(sensor) , name_label(new QLabel()), sensor_type_label(new QLabel()), short_description_label(new QLabel())
{
    setFrameShape(QFrame::StyledPanel);
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    layout->addWidget(name_label);
    layout->addWidget(sensor_type_label);
    layout->addWidget(short_description_label);
    
    connect(this, SIGNAL(clicked()), main, SLOT(update(sensor)));
    sensor.addObserver(this);
}

void SmallSensorView::show() {
    name_label->setText(QString::fromStdString(sensor.getName()));
    sensor_type_label->setText("Type: " + QString::fromStdString(sensor.getSensorType()));
    short_description_label->setText(QString::fromStdString(sensor.getShortDescription()));
}

void SmallSensorView::update(AbstractSensor* sensor) {
    if(sensor != nullptr){
        name_label->setText(QString::fromStdString(sensor->getName()));
        sensor_type_label->setText("Type: " + QString::fromStdString(sensor->getSensorType()));
        short_description_label->setText(QString::fromStdString(sensor->getShortDescription()));
    }else{
        delete this;
    }
}

void SmallSensorView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QFrame::mousePressEvent(event);
}
}
}