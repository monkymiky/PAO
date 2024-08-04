#ifndef DUST25S_H
#define DUST25S_H

#include "AbstractSensor.h"

namespace Sensor{

class Dust25S : public AbstractSensor{
    private:
    double a;
    double b;

    protected:
    double trasmute(double rawMeasure) const override;

    public:
    ~Dust25S();
    Dust25S();
    Dust25S(  const std::string name, 
            const  std::string shortDesc,
            const  std::string longDesc,
            const  std::string xAxisLabel,
            const  unsigned int simulationSpan,
            const  double sensibility,
            const  double maxMeasurable,
            const  double minMeasurable,
            const double a = 1.2,
            const double b = 5);

    void accept(VisitorInterface& visitor) override;
    double getA() const;
    double getB() const;

    void setA( double) ;
    void setB( double) ;
};

}


#endif
