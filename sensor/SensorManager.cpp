#include "SensorManager.h"
#include <algorithm>
#include <iostream>
namespace Sensor{
SensorManager::~SensorManager() {
    cleanSensors();
}

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

void SensorManager::addSensors( std::vector<AbstractSensor*>& sensors) {
    sensors.insert(sensors.end(), sensors.begin(), sensors.end());
}

const std::vector<AbstractSensor*>& SensorManager::getSensors() const {
    return sensors;
}

}
