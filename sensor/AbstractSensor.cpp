#include "AbstractSensor.h"
#include <random>
#include <cmath>
#include <iostream>

namespace Sensor{

AbstractSensor::~AbstractSensor(){}
AbstractSensor::AbstractSensor(): name(""), sensorType(""), shortDescription(""), 
                                longDescription(""),  xAxisLabel(""), yAxisLabel(""),simulationSpan(0),
                                sensibility(0), maxMeasurable(0), minMeasurable(0),min(0),max(0),
                                average(0),variance(0),lastMeasureTime(0),
                                measure(std::vector<std::array<double, 2>>()),
                                observers(std::vector<ObserverInterface*>()){};
AbstractSensor::AbstractSensor( const std::string name,
                                const  std::string sensorType,
                                const  std::string shortDesc,
                                const  std::string longDesc,
                                const  std::string xAxisLabel,
                                const  std::string yAxisLabel,
                                const  unsigned int simulationSpan,
                                const  double sensibility,
                                const  double maxMeasurable,
                                const  double minMeasurable) : 
                                name(name), sensorType(sensorType), shortDescription(shortDesc), 
                                longDescription(longDesc),  xAxisLabel(xAxisLabel), yAxisLabel(yAxisLabel),simulationSpan(simulationSpan),
                                sensibility(sensibility), maxMeasurable(maxMeasurable), minMeasurable(minMeasurable),
                                min(0),max(0),average(0),variance(0),lastMeasureTime(0), 
                                measure(std::vector<std::array<double, 2>>()), observers(std::vector<ObserverInterface*>()){}
                                
void AbstractSensor::addPoint(std::array<double,2>& point){ // in questo progetto non è molto utile come funzione perche non c'è nessun sensore reale che aggiunge le misure una alla volta
    measure.push_back(point);
    if (measure.size() > 1){
        if(max < point[0]) max = point[0];
        else if (min > point[0]) min = point[0];
        if(lastMeasureTime < point[1]) lastMeasureTime = point[1];
        double diff = (point[0] - average);
        variance = ((variance * (measure.size() - 1) + diff * diff)/measure.size() + (diff * average) / measure.size());
        average = (average * (measure.size()-1) + point[0] )/ measure.size();
    }else{
        max = point[0];
        min = point[0];
        average = point[0];
        lastMeasureTime = point[1];
        variance = 0;
    }
    
notifyAllObservers(this);
}
void AbstractSensor::deletePoint(int index){
    measure.erase(measure.begin() + index);
    
notifyAllObservers(this);
}
void AbstractSensor::clearPointVector(){
    measure.clear();
    max = 0;
    min = 0;
    average = 0;
    variance = 0;
    lastMeasureTime = 0;
}
void AbstractSensor::addRawPoint(std::array<double,2>& point){
    std::array<double,2> tmp = {trasmute(point[0]), point[1]};
    addPoint(tmp);
    
notifyAllObservers(this);
}
void AbstractSensor::addPointVector(std::vector<std::array<double, 2>>& vector){
    measure.insert(measure.end(), std::move(vector.begin()), std::move(vector.end()));
    double sum = 0;
    for (std::array<double, 2> point : measure){
        if(point[0] > max) max = point[0];
        else if(point[0]< min ) min = point[0];
        sum += point[0];
        if (point[1] > lastMeasureTime) lastMeasureTime = point[1];
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
            double x = static_cast<int>(lastMeasureTime)  +  simulationSpan;
            std::array<double,2> tmp = {randomMeasure,x};
            addPoint(tmp);
        }
    }
    else{
        for (int i = 0; i < 20; ++i) {
            double y = (rand()%(int)((maxMeasurable - minMeasurable) + minMeasurable +1));
            double x = static_cast<int>(lastMeasureTime) +  simulationSpan;
            std::array<double,2> tmp = {y,x};
            addPoint(tmp);
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

void AbstractSensor::notifyAllObservers(AbstractSensor* sensor) {
    if(observers.size() != 0){
        for(auto observer : observers) observer->update(sensor);
    }
};

// getter -----------------------------------------
const std::vector<ObserverInterface*>& AbstractSensor::getObservers() const{return observers;};
const std::string& AbstractSensor::getName() const {return name;}
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

void  AbstractSensor::setName(const std::string& n)  {
    name = n;
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
