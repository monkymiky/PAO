#include "SensorManager.h"
#include <algorithm>
#include <iostream>
namespace Sensor{
SensorManager::~SensorManager() {
    cleanSensors();
}
void SensorManager::addObserver(ObserverInterface* observer) {
    observers.push_back(observer);
}

void SensorManager::removeObserver(ObserverInterface* observer){
    int size  = observers.size();
    int i = 0;
    while (i < size) {
        if(observers[i] == observer){
            observers.erase(observers.begin() + i);
            size--;
            i--;
        }
        i++;
    }
};

void SensorManager::notifyAllObservers(AbstractSensor* sensor) const {
    if(observers.size() != 0){
        for(auto observer : observers) observer->update(sensor);
    }
};

void SensorManager::addSensor(AbstractSensor* sensor) {
    if (sensor != nullptr) {
        sensors.push_back(sensor);
    }
    notifyAllObservers(sensor);
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

const std::vector<AbstractSensor*>& SensorManager::getSensors() const {
    return sensors;
}

}
