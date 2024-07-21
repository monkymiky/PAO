#include "Aside.h"
#include "SensorDialog.h"
#include <iostream>


namespace Sensor {
namespace View {
void Aside::addNewSensorClicked(){
    SensorDialog* typeDialog = new SensorDialog( manager, qobject_cast<QWidget*>(parent()));
    typeDialog->exec();
};

 Aside::Aside(SensorManager& manager,MainSensorView& main, QWidget* parent)
 : QWidget(parent),
 manager(manager),
 sensorSViewList(std::vector<SmallSensorView*>() ),  
 sensorScrollFrame(new QFrame(this)),
 SensorListLayout(new QVBoxLayout(sensorScrollFrame)),
 main(main)
{
    manager.addObserver(this);

    QVBoxLayout* AsideLayout = new QVBoxLayout(this);
    
    QFrame* topFrame = new QFrame();
    QHBoxLayout* topFrameLayout = new QHBoxLayout(topFrame);
    topFrame->setLayout(topFrameLayout);
    QPushButton *buttonSave = new QPushButton("Salva", topFrame);
    QPushButton *buttonOpen = new QPushButton("Apri", topFrame); 
    QPushButton *buttonClose = new QPushButton("Chiudi", topFrame);
    topFrameLayout->addWidget(buttonSave);
    topFrameLayout->addWidget(buttonOpen); 
    topFrameLayout->addWidget(buttonClose);
    topFrameLayout->addStretch();
    AsideLayout->addWidget(topFrame);

    SensorListLayout->setAlignment(Qt::AlignTop);
    for(auto sensor : manager.getSensors()){
        SmallSensorView* sensorSmallV = new SmallSensorView(*sensor, main, sensorScrollFrame);
        sensorSViewList.push_back(sensorSmallV);
        sensorSmallV->show();
        SensorListLayout->addWidget(sensorSmallV);
        sensor->addObserver(sensorSmallV);
    }
    AsideLayout->addWidget(sensorScrollFrame);

    QScrollArea* SensorScrollArea = new QScrollArea(this);
    SensorScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    SensorScrollArea->setWidgetResizable(true);
    SensorScrollArea->setWidget(sensorScrollFrame);
    AsideLayout->addWidget(SensorScrollArea);

    QPushButton *buttonAdd = new QPushButton("Aggiungi", this);
    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(addNewSensorClicked()));
    AsideLayout->addWidget(buttonAdd);
};

void Aside::show(){
    for(auto sensorView : sensorSViewList){
        sensorView->show();
    }
};

void Aside::update(AbstractSensor* sensor) {
    if (manager.getSensors().size() == sensorSViewList.size() +1){
        AbstractSensor* sensor = manager.getSensors().back();
        SmallSensorView* sensorSmallV = new SmallSensorView(*sensor, main, sensorScrollFrame);
        sensorSViewList.push_back(sensorSmallV);
        sensorSmallV->show();
        SensorListLayout->addWidget(sensorSmallV);
        sensor->addObserver(sensorSmallV);
    }
    else if(manager.getSensors().size() == sensorSViewList.size() -1){
        for(auto sensorSView : sensorSViewList){
            if(sensorSView->getSensor() == sensor){
                sensorSViewList.erase(std::remove(sensorSViewList.begin(), sensorSViewList.end(), sensorSView), sensorSViewList.end());
                SensorListLayout->removeWidget(sensorSView);
                sensorSView->deleteLater();
                break;
            }
        }
    }
    else{
        std::cerr << "Error in Aside::update(AbstractSensor* sensor)" << std::endl;
    }
};
    

}
}