#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include "AbstractSensor.h"
#include "ObserverInterface.h"
namespace Sensor{
class SensorManager {
private:
    std::vector<AbstractSensor*> sensors;
    std::vector<ObserverInterface*> observers;

public:
    ~SensorManager();
    SensorManager() = default;
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator= (const SensorManager&) = delete;
    void addSensor(AbstractSensor* sensor);
    void removeSensor(AbstractSensor* sensor);
    void cleanSensors();
    void addSensors( std::vector<AbstractSensor*>& sensors);
    const std::vector<AbstractSensor*>& getSensors() const;
};
}


#endif 
