#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <string>
#include <vector>
#include <array>
#include "ObserverInterface.h"
#include "VisitorInterface.h"


namespace Sensor{

class AbstractSensor {

    private:
    std::string name;
    std::string sensorType;
    std::string shortDescription;
    std::string longDescription;
    std::string xAxisLabel;
    std::string yAxisLabel;
    unsigned int simulationSpan;
    float sensibility;
    float maxMeasurable;
    float minMeasurable;
    float min;
    float max;
    float average;
    float variance;
    float lastMeasureTime;
    std::vector<std::array<float, 2>> measure; // measure[i][0] == misura;  measure[i][1] == tempo  ------------------- accesso sbagliato ma ilò senso è quello 
    std::vector<ObserverInterface*> observers;
    protected:
    virtual float trasmute(float rawMeasure) const = 0;

    public:

    virtual ~AbstractSensor();
    AbstractSensor(     const std::string name,
                        const  std::string sensorType,
                        const  std::string shortDesc,
                        const  std::string longDesc,
                        const  std::string xAxisLabel,
                        const  std::string yAxisLabel,
                        const  unsigned int simulationSpan,
                        const  float sensibility,
                        const  float maxMeasurable,
                        const  float minMeasurable);
    AbstractSensor();
    void addPoint(std::array<float, 2>&);
    void deletePoint(int);
    void clearPointVector();
    void addRawPoint(std::array<float, 2>&);
    void addPointVector(std::vector<std::array<float, 2>>&);
    virtual void simulate(); 
    virtual void accept(VisitorInterface& visitor) = 0;
    void addObserver(ObserverInterface* observer);
    void removeObserver(ObserverInterface* observer);
    void notifyAllObservers(AbstractSensor* sensor) ;
    // getter 
    const std::vector<ObserverInterface*>& getObservers() const;
    const std::string& getName() const;
    const std::string& getSensorType() const;
    const std::string& getShortDescription() const;
    const std::string& getLongDescription() const;
    const std::string& getXAxisLabel() const;
    const std::string& getYAxisLabel() const;
    unsigned int getSimulationSpan() const;
    float getMaxMeasurable() const;
    float getMinMeasurable() const;
    float getMax() const;
    float getMin() const;
    float getAverage() const;
    float getVariance() const;
    float getSensibility() const;
    const std::vector<std::array<float, 2>>& getMeasure() const;
    // setter
    void setName(const std::string&);
    void setSensorType(const std::string&);
    void setShortDescription(const std::string&);
    void setLongDescription(const std::string&);
    void setXAxisLabel(const std::string&);
    void setSimulationSpan(unsigned int);
    void setMaxMeasurable(float);
    void setMinMeasurable(float);
    void setSensibility(float);
};
}

#endif