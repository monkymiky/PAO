
#include "Dust25S.h"
#include <math.h>
namespace Sensor{

double Dust25S::trasmuteRawVal(double rawMeasure) const  {
    double concentrationPM25 = a * rawMeasure + b;
    return concentrationPM25;
};
Dust25S::Dust25S(): AbstractSensor("", "Resistore a impasto di carbone", "", "", "", "PM 2.5 [µg/m³]" ,0, 0, 0, 0 ) ,a(0), b(0){};
Dust25S::Dust25S(   const  std::string title, 
                    const  std::string shortDesc,
                    const  std::string longDesc,
                    const  std::string xAxisLabel,
                    const  unsigned int simulationSpan,
                    const  double sensibility,
                    const  double maxMeasurable,
                    const  double minMeasurable,
                    const double a,
                    const double b) 
                : AbstractSensor(title, "Resistore a impasto di carbone", shortDesc, longDesc, xAxisLabel, "PM 2.5 [µg/m³]" ,simulationSpan, sensibility, maxMeasurable, minMeasurable ),
                a(a), b(b){};

void Dust25S::accept(ConstVisitorInterface& visitor) const{
    visitor.visitDust25S(*this);
};

// getter
double Dust25S::getA() const {return a;};
double Dust25S::getB() const {return b;};

// setter
void Dust25S::setA( double A){ 
    a=A ;
    notifyAllObservers(this);
}; 
void Dust25S::setB( double B){ 
    b=B ;
    notifyAllObservers(this);
}; 


}
