#include "Aside.h"
#include "SensorDialog.h"
#include <iostream>
#include <QFileDialog>
#include "../sensor/JsonPharser.h"


namespace Sensor {
namespace View {

 Aside::Aside(QWidget* parent):
    QWidget(parent),
    smallSViewList(std::list<SmallSensorView*>() ),  
    sensorScrollFrame(new QFrame(this)),
    
    SensorListLayout(new QVBoxLayout(sensorScrollFrame))
{
    

    QVBoxLayout* AsideLayout = new QVBoxLayout(this);

    SensorListLayout->setAlignment(Qt::AlignTop);
    
    AsideLayout->addWidget(sensorScrollFrame);

    QScrollArea* SensorScrollArea = new QScrollArea(this);
    SensorScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    SensorScrollArea->setWidgetResizable(true);
    SensorScrollArea->setWidget(sensorScrollFrame);
    AsideLayout->addWidget(SensorScrollArea);
}

void Aside::clearSSVList() {
    for(auto sensor : smallSViewList){
        delete sensor;
    }
    smallSViewList.clear();
};

void Aside::deleteSSV(AbstractSensor* sensor) {
    auto it = smallSViewList.begin();
    while (it != smallSViewList.end()) {
        if ((*it)->getSensor() == sensor) {
            delete *it;
            smallSViewList.erase(it);
            break;
        } else {
            ++it;
        }
    }
};

void Aside::addSSV(SmallSensorView* ssv) {
    smallSViewList.push_back(ssv);
    SensorListLayout->addWidget(ssv);
    ssv->show();
};

}
}
