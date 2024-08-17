#include "SensorManager.h"
#include <algorithm>
#include <iostream>
namespace Sensor{
SensorManager::~SensorManager() {
    cleanSensors();
}
SensorManager::SensorManager(): sensors(std::vector<AbstractSensor*>()), observers(std::vector<ObserverInterface*>()){}

void SensorManager::addSensor(AbstractSensor* sensor) {
    if (sensor != nullptr) {
        sensors.push_back(sensor);

    }
    
}

void SensorManager::removeSensor(AbstractSensor* sensor) {
    auto it = std::find(sensors.begin(), sensors.end(), sensor);
    if (it != sensors.end()) {
        sensors.erase(it);
    }
}
void SensorManager::cleanSensors() {
    for (AbstractSensor* sensor : sensors) {
        delete sensor;
    }
    sensors.clear();
}

void SensorManager::addSensors(const std::vector<AbstractSensor*>& sensors) {
    sensors.insert(sensors.end(), sensors.begin(), sensors.end());
}
/*
void SensorManager::addObserver(ObserverInterface *observer)
{
    observers.push_back(observer);
}

void  SensorManager::notifyAllObservers() const{
    for (ObserverInterface* observer : observers) {
        observer->update();
    }
}*/

const std::vector<AbstractSensor*>& SensorManager::getSensors() const {
    return sensors;
}

}
