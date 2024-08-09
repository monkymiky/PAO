#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <vld.h>
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
    double sensibility;
    double maxMeasurable;
    double minMeasurable;
    double min;
    double max;
    double average;
    double variance;
    double lastMeasureTime;
    std::vector<std::array<double, 2>> measure; // measure[i][0] == misura;  measure[i][1] == tempo  ------------------- accesso sbagliato ma ilò senso è quello 
    std::vector<ObserverInterface*> observers;
    protected:
    virtual double trasmute(double rawMeasure) const = 0;

    public:

    virtual ~AbstractSensor();
    AbstractSensor(     const std::string name,
                        const  std::string sensorType,
                        const  std::string shortDesc,
                        const  std::string longDesc,
                        const  std::string xAxisLabel,
                        const  std::string yAxisLabel,
                        const  unsigned int simulationSpan,
                        const  double sensibility,
                        const  double maxMeasurable,
                        const  double minMeasurable);
    AbstractSensor();
    void addPoint(std::array<double, 2>&);
    void deletePoint(int);
    void clearPointVector();
    void addRawPoint(std::array<double, 2>&);
    void addPointVector(std::vector<std::array<double, 2>>&);
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
    double getMaxMeasurable() const;
    double getMinMeasurable() const;
    double getMax() const;
    double getMin() const;
    double getAverage() const;
    double getVariance() const;
    double getSensibility() const;
    const std::vector<std::array<double, 2>>& getMeasure() const;
    // setter
    void setName(const std::string&);
    void setSensorType(const std::string&);
    void setShortDescription(const std::string&);
    void setLongDescription(const std::string&);
    void setXAxisLabel(const std::string&);
    void setSimulationSpan(unsigned int);
    void setMaxMeasurable(double);
    void setMinMeasurable(double);
    void setSensibility(double);
};
}

#endif
