#include "AbstractSensor.h"
#include <random>
#include <cmath>

namespace Sensor{

AbstractSensor::~AbstractSensor(){
    notifyAllObservers(nullptr);
}
AbstractSensor::AbstractSensor(): name(""), sensorType(""), shortDescription(""), 
                                longDescription(""),  xAxisLabel(""), yAxisLabel(""),simulationSpan(0),
                                sensibility(0), maxMeasurable(0), minMeasurable(0),min(0),max(0),
                                average(0),variance(0),lastMeasureTime(0),
                                measure(std::vector<std::array<float, 2>>()),
                                observers(std::vector<ObserverInterface*>()){};
AbstractSensor::AbstractSensor( const std::string name,
                                const  std::string sensorType,
                                const  std::string shortDesc,
                                const  std::string longDesc,
                                const  std::string xAxisLabel,
                                const  std::string yAxisLabel,
                                const  unsigned int simulationSpan,
                                const  float sensibility,
                                const  float maxMeasurable,
                                const  float minMeasurable) : 
                                name(name), sensorType(sensorType), shortDescription(shortDesc), 
                                longDescription(longDesc),  xAxisLabel(xAxisLabel), yAxisLabel(yAxisLabel),simulationSpan(simulationSpan),
                                sensibility(sensibility), maxMeasurable(maxMeasurable), minMeasurable(minMeasurable),
                                min(0),max(0),average(0),variance(0),lastMeasureTime(0), 
                                measure(std::vector<std::array<float, 2>>()), observers(std::vector<ObserverInterface*>()){}
                                
void AbstractSensor::addPoint(std::array<float,2>& point){ // in questo progetto non è molto utile come funzione perche non c'è nessun sensore reale che aggiunge le misure una alla volta
    measure.push_back(point);
    if (measure.size() > 1){
        if(max < point[0]) max = point[0];
        else if (min > point[0]) min = point[0];
        if(lastMeasureTime < point[1]) lastMeasureTime = point[1];
        float diff = (point[0] - average);
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
void AbstractSensor::addRawPoint(std::array<float,2>& point){
    std::array<float,2> tmp = {trasmute(point[0]), point[1]};
    addPoint(tmp);
    
notifyAllObservers(this);
}
void AbstractSensor::addPointVector(std::vector<std::array<float, 2>>& vector){
    measure.insert(measure.end(), std::move(vector.begin()), std::move(vector.end()));
    float sum = 0;
    for (std::array<float, 2> point : measure){
        if(point[0] > max) max = point[0];
        else if(point[0]< min ) min = point[0];
        sum += point[0];
        if (point[1] > lastMeasureTime) lastMeasureTime = point[1];
    }
    average = sum / measure.size();
    float squared_deviations = 0;
     for (std::array<float, 2> point : measure){
        float deviation = point[0] - average;
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
        std::normal_distribution<float> distribution(average, std::sqrt(variance)); 
        // Generate 20 random values
        float randomMeasure;
        for (int i = 0; i < 20; ++i) {
            do{
                randomMeasure = distribution(generator);
            }while(randomMeasure > minMeasurable && randomMeasure < maxMeasurable);
            std::array<float,2> tmp = {randomMeasure,static_cast<int>(lastMeasureTime) +1 + i * simulationSpan};
            addPoint(tmp);
        }
    }
    else{
        for (int i = 0; i < 20; ++i) {
            std::array<float,2> tmp = {(rand()%(int)((maxMeasurable - minMeasurable) + minMeasurable)),static_cast<int>(lastMeasureTime) +1 + i * simulationSpan};
            addPoint(tmp);
        }
    }
notifyAllObservers(this);
}

void AbstractSensor::addObserver(ObserverInterface* observer) {
    observers.push_back(observer);
}

void AbstractSensor::removeObserver(ObserverInterface* observer){
    for (int i = 0; i < observers.size(); i++) {
        if(observers[i] == observer) observers.erase(observers.begin() + i);
    }
};

void AbstractSensor::notifyAllObservers(AbstractSensor* sensor) {
    for(auto observer : observers) observer->update(sensor);
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
float AbstractSensor::getMaxMeasurable() const {return maxMeasurable;}
float AbstractSensor::getMinMeasurable() const {return minMeasurable;}
float AbstractSensor::getMax() const {return max;}
float AbstractSensor::getMin() const {return min;}
float AbstractSensor::getAverage() const {return average;}
float AbstractSensor::getVariance() const {return variance;}
float AbstractSensor::getSensibility() const {return sensibility;}
const std::vector<std::array<float, 2>>& AbstractSensor::getMeasure() const{return measure;};

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
void  AbstractSensor::setMaxMeasurable(float maxM)  {
    maxMeasurable = maxM;
    
    notifyAllObservers(this);
}
void  AbstractSensor::setMinMeasurable(float minM)  {
    minMeasurable = minM;
    notifyAllObservers(this);
}
void  AbstractSensor::setSensibility(float sen)  {
    simulationSpan = sen;
    notifyAllObservers(this);
}


}