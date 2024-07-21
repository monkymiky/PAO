#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include "AbstractSensor.h"
#include "ObserverInterface.h"
namespace Sensor{
class SensorManager {
private:
    std::vector<AbstractSensor*> sensorList;
    std::vector<ObserverInterface*> observers;

public:
    SensorManager();
    ~SensorManager();

    void addSensor(AbstractSensor* sensor);
    void removeSensor(AbstractSensor* sensor);
    void cleanSensors();
    void addSensors(const std::vector<AbstractSensor*>& sensors);
    void addObserver(ObserverInterface* observer);
    void notifyAllObservers() const ;
    const std::vector<AbstractSensor*>& getSensors() const;
};
}


#endif 