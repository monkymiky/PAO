
#include "HumidityS.h"
#include <math.h>
#include <vector>

namespace Sensor{

void HumidityNTCS::createInterpolationTable(){
    for (int i = 0; i <101; ++i) {
        // Calculate the rawMeasure for a relative humidity value
        double resistenza = 100 + (900.0 / (100)) * i;  // Resistance varies from 100 to 1000 Ohms
        double UR = 100 * (a + b * log(resistenza) + c * pow(log(resistenza), 2));
        interpolationTable.push_back(UR);
    } 
};
double HumidityNTCS::trasmuteRawVal(double rawMeasure) const  {
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
    double interpolatedHumidity = 0.0;
    if (inf == sup) {
        interpolatedHumidity = interpolationTable[inf];
    } else {
        double humidityInf = interpolationTable[inf];
        double humiditySup = interpolationTable[sup];
        double rawMeasureInf = 100 + (900.0 / (interpolationTable.size() - 1)) * inf;
        double rawMeasureSup = 100 + (900.0 / (interpolationTable.size() - 1)) * sup;

        interpolatedHumidity = humidityInf + 
        ((rawMeasure - rawMeasureInf) / (rawMeasureSup - rawMeasureInf)) * 
        (humiditySup - humidityInf);
    }

    return interpolatedHumidity;
};
HumidityNTCS::HumidityNTCS(): AbstractSensor("", "Resistenza NTC", "", "", "","Umidità relativa %", 0, 0, 0, 0 ),a(0), b(0), c(0){};
HumidityNTCS::HumidityNTCS( const std::string title, 
                            const  std::string shortDesc,
                            const  std::string longDesc,
                            const  std::string xAxisLabel,
                            const  unsigned int simulationSpan,
                            const  double sensibility,
                            const  double maxMeasurable,
                            const  double minMeasurable,
                            const double a,
                            const double b,
                            const double c) 
                            : AbstractSensor(title, "Resistenza NTC", shortDesc, longDesc, xAxisLabel,"Umidità relativa %", simulationSpan, sensibility, maxMeasurable, minMeasurable ),
                            a(a), b(b), c(c)
                            {
                                createInterpolationTable();
                            };

void HumidityNTCS::accept(ConstVisitorInterface& visitor) const{
    visitor.visitHumidityNTCS(*this);
};

// getter
double HumidityNTCS::getA() const {return a;};
double HumidityNTCS::getB() const {return b;};
double HumidityNTCS::getC() const {return c;};

// setter
void HumidityNTCS::setA( double A){ 
    a=A ;
    if(b != 0 && c != 0) createInterpolationTable();
    notifyAllObservers(this);
    }
void HumidityNTCS::setB( double B){ 
    b=B ;
    if(a != 0 && c != 0) createInterpolationTable();
    notifyAllObservers(this);
    }
void HumidityNTCS::setC( double C){ 
    c=C ;
    if(a != 0 && b != 0) createInterpolationTable();
    notifyAllObservers(this);
    }


}
