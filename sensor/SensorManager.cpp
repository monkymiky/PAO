#include "SensorManager.h"
#include <algorithm>
#include <iostream>
namespace Sensor{
SensorManager::~SensorManager() {
    cleanSensors();
}
SensorManager::SensorManager(): sensorList(std::vector<AbstractSensor*>()), observers(std::vector<ObserverInterface*>()){}

void SensorManager::addSensor(AbstractSensor* sensor) {
    if (sensor != nullptr) {
        sensorList.push_back(sensor);
        notifyAllObservers();
    }
    
}

void SensorManager::removeSensor(AbstractSensor* sensor) {
    auto it = std::find(sensorList.begin(), sensorList.end(), sensor);
    if (it != sensorList.end()) {
        sensorList.erase(it);
        notifyAllObservers();
    }
}

void SensorManager::cleanSensors() {
    for (AbstractSensor* sensor : sensorList) {
        delete sensor;
    }
    sensorList.clear();
    notifyAllObservers();
}

void SensorManager::addSensors(const std::vector<AbstractSensor*>& sensors) {
    sensorList.insert(sensorList.end(), sensors.begin(), sensors.end());
    notifyAllObservers();
}

void SensorManager::addObserver(ObserverInterface *observer)
{
    observers.push_back(observer);
}

void  SensorManager::notifyAllObservers() const{
    for (ObserverInterface* observer : observers) {
        observer->update();
    }
}

const std::vector<AbstractSensor*>& SensorManager::getSensors() const {
    return sensorList;
}

}
