#include "TemperatureS.h"
#include <vector>
#include <math.h>

namespace Sensor{

float TemperaturePRTS::simulatePRTResistanceMeasurement(float temperature){
// Calculate the PRT resistance at the specified temperature
  float R = R0 * (1 + alpha * temperature 
                    + beta * temperature * temperature 
                    + gamma * temperature * temperature * temperature 
                    + delta * temperature * temperature * temperature * temperature 
                    + epsilon * temperature * temperature * temperature * temperature * temperature 
                    + zeta * temperature * temperature * temperature * temperature * temperature * temperature);
  return R;
};

void TemperaturePRTS::createInterpolationTable(){
    for (float temperature = (int)getMinMeasurable(); temperature <= (int)getMaxMeasurable()+1; temperature += 1.0) {
    float resistance = simulatePRTResistanceMeasurement(temperature);
    interpolationTable.push_back(resistance);
  }
};
float TemperaturePRTS::trasmute(float resistance) const  {
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
    float interpolatedTemperature = 0.0;
    if (inf == sup) {
        interpolatedTemperature = interpolationTable[inf];
    } else {
        float temperatureInf = interpolationTable[inf];
        float temperatureSup = interpolationTable[sup];
        float resistanceInf = interpolationTable[inf];
        float resistanceSup = interpolationTable[sup];

        interpolatedTemperature = temperatureInf + 
        ((resistance - resistanceInf) / (resistanceSup - resistanceInf)) * 
        (temperatureSup - temperatureInf);
    }

    return interpolatedTemperature;
};

TemperaturePRTS::TemperaturePRTS(): AbstractSensor("", "Resistenza PRT", "", "", "","Temperatura [C°]", 0, 0, 0, 0 ),R0(0), alpha(0), beta(0), gamma(0), delta(0), epsilon(0), zeta(0), interpolationTable(std::vector<float>()){};

TemperaturePRTS::TemperaturePRTS(   const std::string name, 
                                    const  std::string shortDesc,
                                    const  std::string longDesc,
                                    const  std::string xAxisLabel,
                                    const  unsigned int simulationSpan,
                                    const  float sensibility,
                                    const  float maxMeasurable,
                                    const  float minMeasurable,
                                    const float R0 = 100,
                                    const float alpha = 3.9083e-3,
                                    const float beta = -5.6823e-6,
                                    const float gamma = -4.1016e-8,
                                    const float delta = 1.27e-10,
                                    const float epsilon = -1.76e-13,
                                    const float zeta =  2.04e-16) 
                                    : AbstractSensor(name, "Resistenza PRT", shortDesc, longDesc, xAxisLabel,"Temperatura [C°]", simulationSpan, sensibility, maxMeasurable, minMeasurable ),
                                    R0(R0), alpha(alpha), beta(beta), gamma(gamma), delta(delta), epsilon(epsilon), zeta(zeta), interpolationTable(std::vector<float>())
                                    {
                                        createInterpolationTable();
                                    };

void TemperaturePRTS::accept(VisitorInterface& visitor){
    visitor.visitTemperaturePRTS(*this);
};

// getter
float TemperaturePRTS::getR0() const {return R0;};
float TemperaturePRTS::getAlpha() const {return alpha;};
float TemperaturePRTS::getBeta() const {return beta;};
float TemperaturePRTS::getGamma() const {return gamma;};
float TemperaturePRTS::getDelta() const {return delta;};
float TemperaturePRTS::getEpsilon() const {return epsilon;};
float TemperaturePRTS::getZeta() const {return zeta;};
// setter
void TemperaturePRTS::setR0( float r0){ 
    R0=r0 ;
    if(alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setAlpha( float a){ 
    alpha=a ;
    if(R0!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setBeta( float b){
    beta = b;
    if(R0!=0 && alpha!=0 && gamma!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setGamma( float g){
    gamma =g ;
    if(R0!=0 && alpha!=0 && beta!=0 && delta!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setDelta( float d){ 
    delta= d;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && epsilon!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setEpsilon( float e){
    epsilon =e ;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && zeta!=0)createInterpolationTable();
    notifyAllObservers(this);}
void TemperaturePRTS::setZeta( float z){ 
    zeta=z ;
    if(R0!=0 && alpha!=0 && beta!=0 && gamma!=0 && delta!=0 && epsilon!=0)createInterpolationTable();
    notifyAllObservers(this);}

}
