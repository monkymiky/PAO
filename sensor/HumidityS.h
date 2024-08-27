#ifndef HUMIDITYS_H
#define HUMIDITYS_H

#include "AbstractSensor.h"

namespace Sensor{

class HumidityNTCS : public AbstractSensor{
    private:
    double a;
    double b;
    double c;
    std::vector<double> interpolationTable;
    void createInterpolationTable();
    protected:
    double trasmuteYVal(double rawMeasure) const override;

    public:
    ~HumidityNTCS() = default;
    HumidityNTCS();
    HumidityNTCS(   const std::string name, // resistenza NTC
                    const  std::string shortDesc,
                    const  std::string longDesc,
                    const  std::string xAxisLabel,
                    const  unsigned int simulationSpan,
                    const  double sensibility,
                    const  double maxMeasurable,
                    const  double minMeasurable,
                    const double a,
                    const double b,
                    const double c);
    
    void accept(ConstVisitorInterface& visitor) const override;

    double getA() const;
    double getB() const;
    double getC() const;
   

    void setA( double) ;
    void setB( double) ;
    void setC( double) ;
    
};

}


#endif
