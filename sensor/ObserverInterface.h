#ifndef SENSOR_OBSERVER_INTERFACE_H
#define SENSOR_OBSERVER_INTERFACE_H

namespace Sensor {

class AbstractSensor;

class ObserverInterface {
  public:
    virtual ~ ObserverInterface() = default;
    virtual void update(AbstractSensor* sensor = nullptr) = 0;
    
};

}

#endif