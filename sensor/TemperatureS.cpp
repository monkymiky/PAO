#include "TemperatureS.h"
#include <vector>
#include <math.h>

namespace Sensor{

double TemperaturePRTS::simulatePRTResistanceMeasurement(double temperature){
// Calculate the PRT resistance at the specified temperature
  double R = R0 * (1 + alpha * temperature 
                    + beta * temperature * temperature 
                    + gamma * temperature * temperature * temperature 
                    + delta * temperature * temperature * temperature * temperature 
                    + epsilon * temperature * temperature * temperature * temperature * temperature 
                    + zeta * temperature * temperature * temperature * temperature * temperature * temperature);
  return R;
};

void TemperaturePRTS::createInterpolationTable(){
    for (double temperature = (int)getMinMeasurable(); temperature <= (int)getMaxMeasurable()+1; temperature += 1.0) {
    double resistance = simulatePRTResistanceMeasurement(temperature);
    interpolationTable.push_back(resistance);
  }
};
double TemperaturePRTS::trasmute(double resistance) const  {
    int inf = 0;
    int sup = interpolationTable.size() - 1;

    while (inf < sup) { 
        int mean = (inf + sup) / 2;

        if (resistance < interpolationTable[mean]) {
        sup = mean;
        } else {
        inf = mean + 1;
        }
    }

    // Interpolate the temperature between the two values in the interpolationTable
    double interpolatedTemperature = 0.0;
    if (inf == sup) {
        interpolatedTemperature = interpolationTable[inf];
    } else {
        double temperatureInf = interpolationTable[inf];
        double temperatureSup = interpolationTable[sup];
        double resistanceInf = interpolationTable[inf];
        double resistanceSup = interpolationTable[sup];

        interpolatedTemperature = temperatureInf + 
        ((resistance - resistanceInf) / (resistanceSup - resistanceInf)) * 
        (temperatureSup - temperatureInf);
    }

    return interpolatedTemperature;
};

TemperaturePRTS::TemperaturePRTS(): AbstractSensor("", "Resistenza PRT", "", "", "","Temperatura [C°]", 0, 0, 0, 0 ),R0(0), alpha(0), beta(0), gamma(0), delta(0), epsilon(0), zeta(0), interpolationTable(std::vector<double>()){};

TemperaturePRTS::TemperaturePRTS(   const std::string name, 
                                    const  std::string shortDesc,
                                    const  std::string longDesc,
                                    const  std::string xAxisLabel,
                                    const  unsigned int simulationSpan,
                                    const  double sensibility,
                                    const  double maxMeasurable,
                                    const  double minMeasurable,
                                    const double R0 = 100,
                                    const double alpha = 3.9083e-3,
                                    const double beta = -5.6823e-6,
                                    const double gamma = -4.1016e-8,
                                    const double delta = 1.27e-10,
                                    const double epsilon = -1.76e-13,
                                    const double zeta =  2.04e-16) 
                                    : AbstractSensor(name, "Resistenza PRT", shortDesc, longDesc, xAxisLabel,"Temperatura [C°]", simulationSpan, sensibility, maxMeasurable, minMeasurable ),
                                    R0(R0), alpha(alpha), beta(beta), gamma(gamma), delta(delta), epsilon(epsilon), zeta(zeta), interpolationTable(std::vector<double>())
                                    {
                                        createInterpolationTable();
                                    };

void TemperaturePRTS::accept(VisitorInterface& visitor){
    visitor.visitTemperaturePRTS(*this);
};

// getter
double TemperaturePRTS::getR0() const {return R0;};
double TemperaturePRTS::getAlpha() const {return alpha;};
double TemperaturePRTS::getBeta() const {return beta;};
double TemperaturePRTS::getGamma() const {return gamma;};
double TemperaturePRTS::getDelta() const {return delta;};
double TemperaturePRTS::getEpsilon() const {return epsilon;};
double TemperaturePRTS::getZeta() const {return zeta;};
// setter
void TemperaturePRTS::setR0( double r0){ 
    R0=r0 ;
    if(alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setAlpha( double a){ 
    alpha=a ;
    if(R0!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setBeta( double b){
    beta = b;
    if(R0!=0 && alpha!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setGamma( double g){
    gamma =g ;
    if(R0!=0 && alpha!=0 && beta!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setDelta( double d){ 
    delta= d;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setEpsilon( double e){
    epsilon =e ;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setZeta( double z){ 
    zeta=z ;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0)createInterpolationTable();
    notifyAllObservers(this);}

}
