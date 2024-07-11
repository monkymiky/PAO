#include "SensorManager.h"
#include <algorithm>
namespace Sensor{
SensorManager::~SensorManager() {
    cleanSensors();
    
}
SensorManager::SensorManager(): sensorList(std::vector<AbstractSensor*>()), observers(std::vector<ObserverInterface*>()){}

void SensorManager::addSensor(AbstractSensor* sensor) {
    if (sensor != nullptr) {
        sensorList.push_back(sensor);
    }
}

void SensorManager::removeSensor(AbstractSensor* sensor) {
    auto it = std::find(sensorList.begin(), sensorList.end(), sensor);
    if (it != sensorList.end()) {
        sensorList.erase(it);
    }
}

void SensorManager::cleanSensors() {
    sensorList.clear();
}

void SensorManager::addSensors(const std::vector<AbstractSensor*>& sensors) {
    sensorList.insert(sensorList.end(), sensors.begin(), sensors.end());
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
