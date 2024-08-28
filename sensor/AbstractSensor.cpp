#include "AbstractSensor.h"
#include <random>
#include <cmath>
#include <iostream>
#include <exception>


namespace Sensor{

AbstractSensor::AbstractSensor(): title(""), sensorType(""), shortDescription(""), 
                                longDescription(""),  xAxisLabel(""), yAxisLabel(""),simulationSpan(0),
                                sensibility(0), maxMeasurable(0), minMeasurable(0),min(0),max(0),
                                average(0),variance(0),lastXVal(0){};
AbstractSensor::AbstractSensor( const  std::string title,
                                const  std::string sensorType,
                                const  std::string shortDesc,
                                const  std::string longDesc,
                                const  std::string xAxisLabel,
                                const  std::string yAxisLabel,
                                const  unsigned int simulationSpan,
                                const  double sensibility,
                                const  double maxMeasurable,
                                const  double minMeasurable) : 
                                title(title), sensorType(sensorType), shortDescription(shortDesc), 
                                longDescription(longDesc),  xAxisLabel(xAxisLabel), yAxisLabel(yAxisLabel),simulationSpan(simulationSpan),
                                sensibility(sensibility), maxMeasurable(maxMeasurable), minMeasurable(minMeasurable),
                                min(0),max(0),average(0),variance(0),lastXVal(0){}
                                
void AbstractSensor::addPoint(const std::array<double,2>& newPoint){ 
    if(newPoint[1] > lastXVal) {
        measure.push_back(newPoint);
    }else{
        for(auto it = measure.begin(); it != measure.end(); it++){
            if(it->at(1) > newPoint[1]){
                measure.insert(it,newPoint);
                break;
            }else if(it->at(1) == newPoint[1]) throw DuplicatedXValueException();
        }
    }
    if (measure.size() >= 1){
        if(max < newPoint[0]) max = newPoint[0];
        else if (min > newPoint[0]) min = newPoint[0];
        if(lastXVal < newPoint[1]) lastXVal = newPoint[1];
        double diff = (newPoint[0] - average);
        average = (average * (measure.size()-1) + newPoint[0] )/ measure.size();
        variance = ((variance * (measure.size()-1) + diff * diff)/measure.size());
    }else{
        max = newPoint[0];
        min = newPoint[0];
        average = newPoint[0];
        lastXVal = newPoint[1];
        variance = 0;
    }
    notifyAllObservers(this);
}
void AbstractSensor::deletePointAt(int index){
    measure.erase(measure.begin() + index);
    notifyAllObservers(this);
}
void AbstractSensor::clearPoints(){
    measure.clear();
    max = 0;
    min = 0;
    average = 0;
    variance = 0;
    lastXVal = 0;
}

void AbstractSensor::addPoints(const std::vector<std::array<double, 2>>& points){
    measure.insert(measure.end(), std::move(points.begin()), std::move(points.end()));
    double sum = 0;
    for (std::array<double, 2> point : measure){
        if(point[0] > max) max = point[0];
        else if(point[0]< min ) min = point[0];
        sum += point[0];
        if (point[1] > lastXVal) lastXVal = point[1];
    }
    average = sum / measure.size();
    double squared_deviations = 0;
     for (std::array<double, 2> point : measure){
        double deviation = point[0] - average;
        squared_deviations += deviation * deviation;
     }
    variance = squared_deviations / measure.size();
    notifyAllObservers(this);
}
void AbstractSensor::simulate(){
    if(measure.size() >= 5) {
        // Create a normal distribution object
        std::random_device rd; // seed for random generator
        std::mt19937 generator(rd()); // random numbers generator
        std::normal_distribution<double> distribution(average, std::sqrt(variance)); 
        // Generate 20 random values
        double randomMeasure;
        for (int i = 0; i < 20; ++i) {
            do{
                randomMeasure = distribution(generator);
            }while(randomMeasure < minMeasurable || randomMeasure > maxMeasurable);
            double x = static_cast<int>(lastXVal)  +  simulationSpan;
            std::array<double,2> point = {randomMeasure,x};
            addPoint(point);
        }
    }
    else{
        for (int i = 0; i < 20; ++i) {
            double y = (rand()%(int)((maxMeasurable - minMeasurable) + minMeasurable +1));
            double x = static_cast<int>(lastXVal) +  simulationSpan;
            std::array<double,2> point = {y,x};
            addPoint(point);
        }
    }
    notifyAllObservers(this);
}

void AbstractSensor::addObserver(ObserverInterface* observer) {
    observers.push_back(observer);
}

void AbstractSensor::removeObserver(ObserverInterface* observer){
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

void AbstractSensor::notifyAllObservers(AbstractSensor* sensor) const {
    if(observers.size() != 0){
        for(auto observer : observers) observer->update(sensor);
    }
};

// getter -----------------------------------------
const std::string& AbstractSensor::getTitle() const {return title;}
const std::string& AbstractSensor::getSensorType() const {return sensorType;}
const std::string& AbstractSensor::getShortDescription() const {return shortDescription;}
const std::string& AbstractSensor::getLongDescription() const {return longDescription;}
const std::string& AbstractSensor::getXAxisLabel() const {return xAxisLabel;}
const std::string& AbstractSensor::getYAxisLabel() const{return yAxisLabel;};
unsigned int AbstractSensor::getSimulationSpan() const {return simulationSpan;}
double AbstractSensor::getMaxMeasurable() const {return maxMeasurable;}
double AbstractSensor::getMinMeasurable() const {return minMeasurable;}
double AbstractSensor::getMax() const {return max;}
double AbstractSensor::getMin() const {return min;}
double AbstractSensor::getAverage() const {return average;}
double AbstractSensor::getVariance() const {return variance;}
double AbstractSensor::getSensibility() const {return sensibility;}
const std::vector<std::array<double, 2>>& AbstractSensor::getMeasure() const{return measure;};

// setter --------------------------------

void  AbstractSensor::setTitle(const std::string& n)  {
    title = n;
    notifyAllObservers(this);
}
void  AbstractSensor::setSensorType(const std::string& st)  {
    sensorType = st;
    notifyAllObservers(this);
}
void  AbstractSensor::setShortDescription(const std::string& sd)  {
    shortDescription = sd;
    notifyAllObservers(this);
}
void  AbstractSensor::setLongDescription(const std::string& ld)  {
    longDescription = ld;
    notifyAllObservers(this);
}
void  AbstractSensor::setXAxisLabel(const std::string& xal)  {
    xAxisLabel = xal;
    notifyAllObservers(this);
}
void  AbstractSensor::setSimulationSpan( unsigned int sp)   {
    simulationSpan = sp;
    notifyAllObservers(this);
}
void  AbstractSensor::setMaxMeasurable(double maxM)  {
    maxMeasurable = maxM;
    
    notifyAllObservers(this);
}
void  AbstractSensor::setMinMeasurable(double minM)  {
    minMeasurable = minM;
    notifyAllObservers(this);
}
void  AbstractSensor::setSensibility(double sen)  {
    simulationSpan = sen;
    notifyAllObservers(this);
}


}
