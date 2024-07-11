#ifndef HUMIDITYS_H
#define HUMIDITYS_H

#include "AbstractSensor.h"

namespace Sensor{

class HumidityNTCS : public AbstractSensor{
    private:
    float a;
    float b;
    float c;
    std::vector<float> interpolationTable;
    void createInterpolationTable();
    protected:
    float trasmute(float rawMeasure) const override;

    public:
    ~HumidityNTCS();
    HumidityNTCS();
    HumidityNTCS(   const std::string name, // resistenza NTC
                    const  std::string shortDesc,
                    const  std::string longDesc,
                    const  std::string xAxisLabel,
                    const  unsigned int simulationSpan,
                    const  float sensibility,
                    const  float maxMeasurable,
                    const  float minMeasurable,
                    const float a,
                    const float b,
                    const float c);
    
    void accept(VisitorInterface& visitor) override;

    float getA() const;
    float getB() const;
    float getC() const;
   

    void setA( float) ;
    void setB( float) ;
    void setC( float) ;
    
};

}


#endif
