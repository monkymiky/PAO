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
    sensorOutFrame(new QFrame(this)),
    sensorsLayout(new QVBoxLayout(sensorOutFrame)),
    search(new QLineEdit(this))
{
    QVBoxLayout* AsideLayout = new QVBoxLayout(this);

    QFrame* searchFrame = new  QFrame(this);
    QHBoxLayout * searchFrameLayout = new QHBoxLayout(searchFrame);
    QPushButton* lens = new QPushButton("cerca",searchFrame);
    searchFrameLayout->addWidget(search);
    searchFrameLayout->addWidget(lens);
    connect(lens, SIGNAL(clicked()), this, SLOT(searchSSV()));

    AsideLayout->addWidget(searchFrame);

    sensorsLayout->setAlignment(Qt::AlignTop);
    AsideLayout->addWidget(sensorOutFrame);

    QScrollArea* SensorScrollArea = new QScrollArea(this);
    SensorScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    SensorScrollArea->setWidgetResizable(true);
    SensorScrollArea->setWidget(sensorOutFrame);
    AsideLayout->addWidget(SensorScrollArea);
}

void Aside::clearAllSSV() {
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
    sensorsLayout->addWidget(ssv);
    ssv->show();
};


void Aside::searchSSV(){
    std::string searched = search->text().toStdString();
    searched = searched.substr(0, searched.find_last_not_of(" ") + 1);
    searched = searched.substr(searched.find_first_not_of(" "));
    if(searched == ""){
        for(auto& ssv : smallSViewList){
            ssv->show();
        }
    }else{
        for(auto& ssv : smallSViewList){
            std::string title = ssv->getSensor()->getName();
            if(title.find(searched) != std::string::npos){
                ssv->show();
            }else{
                ssv->hide();
            }
        }
    }
}
}
}
