#include "Aside.h"
#include "SensorDialog.h"


namespace Sensor {
namespace View {
void Aside::addNewSensorClicked(){
    SensorDialog* typeDialog = new SensorDialog(&sensorManager);
    typeDialog->setAttribute(Qt::WA_DeleteOnClose);
    typeDialog->exec();
};

 Aside::Aside(SensorManager& sensorManager,MainSensorView* main, QWidget* parent)
 : QWidget(parent),
 sensorManager(sensorManager),
 sensorViewList(std::vector<SmallSensorView*>() ), 
 SensorScrollArea(new QScrollArea(this)), 
 SensorListLayout(new QHBoxLayout(SensorScrollArea)),
 main(main)
{
    QVBoxLayout* AsideLayout = new QVBoxLayout(this);
    AsideLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QFrame* topFrame = new QFrame();
    QHBoxLayout* frameLayout = new QHBoxLayout(topFrame);
    topFrame->setLayout(frameLayout);
    QPushButton *buttonSave = new QPushButton("Salva", topFrame);
    QPushButton *buttonOpen = new QPushButton("Apri", topFrame); 
    QPushButton *buttonClose = new QPushButton("Chiudi", topFrame);
    frameLayout->addWidget(buttonSave);
    frameLayout->addWidget(buttonOpen); 
    frameLayout->addWidget(buttonClose);
    AsideLayout->addWidget(topFrame);

    for(auto sensor : sensorManager.getSensors()){
        SmallSensorView* sensorV = new SmallSensorView(*sensor, main, SensorScrollArea);
        sensorViewList.push_back(sensorV);
        sensorV->show();
        SensorListLayout->addWidget(sensorV);
        sensor->addObserver(this);
    }
    AsideLayout->addWidget(SensorScrollArea);

    QPushButton *buttonAdd = new QPushButton("Aggiungi", this);
    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(addNewSensorClicked()));
    AsideLayout->addWidget(buttonAdd);
};

void Aside::show(){
    for(auto sensorView : sensorViewList){
        sensorView->show();
    }
};

void Aside::update(AbstractSensor* sensor) {
    QLayoutItem* item;
    while ((item = SensorListLayout->takeAt(0)) != nullptr)
    {
        if (QWidget* widget = item->widget())
        {
            SensorListLayout->removeWidget(widget);
            widget->deleteLater();
        }
    }
    for(auto sensor : sensorManager.getSensors()){
        SmallSensorView* sensorV = new SmallSensorView(*sensor, main, SensorScrollArea);
        sensorViewList.push_back(sensorV);
        sensorV->show();
        SensorListLayout->addWidget(sensorV);
        if(sensor != nullptr){
            sensor->removeObserver(this);
        }
    }
};
    

}
}