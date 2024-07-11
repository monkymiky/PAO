
#include "HumidityS.h"
#include <math.h>
#include <vector>

namespace Sensor{

HumidityNTCS::~HumidityNTCS(){}; 

void HumidityNTCS::createInterpolationTable(){
    for (int i = 0; i <101; ++i) {
        // Calculate the rawMeasure for a relative humidity value
        float resistenza = 100 + (900.0 / (100)) * i;  // Resistance varies from 100 to 1000 Ohms
        float UR = 100 * (a + b * log(resistenza) + c * pow(log(resistenza), 2));
        interpolationTable.push_back(UR);
    } 
};
float HumidityNTCS::trasmute(float rawMeasure) const  {
    int inf = 0;
    int sup = interpolationTable.size() - 1;

    while (inf < sup) {
        int mean = (inf + sup) / 2;

        if (rawMeasure < interpolationTable[mean]) {
        sup = mean;
        } else {
        inf = mean + 1;
        }
    }

    // Interpolate the humidity between the two values in the interpolationTable
    float interpolatedHumidity = 0.0;
    if (inf == sup) {
        interpolatedHumidity = interpolationTable[inf];
    } else {
        float humidityInf = interpolationTable[inf];
        float humiditySup = interpolationTable[sup];
        float rawMeasureInf = 100 + (900.0 / (interpolationTable.size() - 1)) * inf;
        float rawMeasureSup = 100 + (900.0 / (interpolationTable.size() - 1)) * sup;

        interpolatedHumidity = humidityInf + 
        ((rawMeasure - rawMeasureInf) / (rawMeasureSup - rawMeasureInf)) * 
        (humiditySup - humidityInf);
    }

    return interpolatedHumidity;
};
HumidityNTCS::HumidityNTCS(): AbstractSensor("", "Resistenza NTC", "", "", "","Umidità relativa %", 0, 0, 0, 0 ),a(0), b(0), c(0), interpolationTable(std::vector<float>()){};
HumidityNTCS::HumidityNTCS( const std::string name, 
                            const  std::string shortDesc,
                            const  std::string longDesc,
                            const  std::string xAxisLabel,
                            const  unsigned int simulationSpan,
                            const  float sensibility,
                            const  float maxMeasurable,
                            const  float minMeasurable,
                            const float a,
                            const float b,
                            const float c) 
                            : AbstractSensor(name, "Resistenza NTC", shortDesc, longDesc, xAxisLabel,"Umidità relativa %", simulationSpan, sensibility, maxMeasurable, minMeasurable ),
                            a(a), b(b), c(c), interpolationTable(std::vector<float>())
                            {
                                createInterpolationTable();
                            };

void HumidityNTCS::accept(VisitorInterface& visitor){
    visitor.visitHumidityNTCS(*this);
};

// getter
float HumidityNTCS::getA() const {return a;};
float HumidityNTCS::getB() const {return b;};
float HumidityNTCS::getC() const {return c;};

// setter
void HumidityNTCS::setA( float A){ 
    a=A ;
    if(b != 0 && c != 0) createInterpolationTable();
    notifyAllObservers(this);
    }
void HumidityNTCS::setB( float B){ 
    b=B ;
    if(a != 0 && c != 0) createInterpolationTable();
    notifyAllObservers(this);
    }
void HumidityNTCS::setC( float C){ 
    c=C ;
    if(a != 0 && b != 0) createInterpolationTable();
    notifyAllObservers(this);
    }


}
