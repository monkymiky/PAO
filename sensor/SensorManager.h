#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include "AbstractSensor.h"
#include "ObserverInterface.h"
namespace Sensor{
class SensorManager{
private:
    std::vector<AbstractSensor*> sensors;
    std::vector<ObserverInterface*> observers;
    void notifyAllObservers(AbstractSensor* sensor) const ;
public:
    ~SensorManager();
    SensorManager() = default;
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator= (const SensorManager&) = delete;
    void addObserver(ObserverInterface* observer);
    void removeObserver(ObserverInterface* observer);
    void addSensor(AbstractSensor* sensor);
    void removeSensor(AbstractSensor* sensor);
    void cleanSensors();
    const std::vector<AbstractSensor*>& getSensors() const;
};
}


#endif 
