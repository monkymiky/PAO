#ifndef DUST25S_H
#define DUST25S_H

#include "AbstractSensor.h"

namespace Sensor{

class Dust25S : public AbstractSensor{
    private:
    float a;
    float b;

    protected:
    float trasmute(float rawMeasure) const override;

    public:
    ~Dust25S();
    Dust25S();
    Dust25S(  const std::string name, 
            const  std::string shortDesc,
            const  std::string longDesc,
            const  std::string xAxisLabel,
            const  unsigned int simulationSpan,
            const  float sensibility,
            const  float maxMeasurable,
            const  float minMeasurable,
            const float a = 1.2,
            const float b = 5);

    void accept(VisitorInterface& visitor) override;
    float getA() const;
    float getB() const;

    void setA( float) ;
    void setB( float) ;
};

}


#endif
