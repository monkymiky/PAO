#ifndef TEMPERATURE_PRT_SENSOR_H
#define TEMPERATURE_PRT_SENSOR_H

#include "AbstractSensor.h"

namespace Sensor{

class TemperaturePRTS : public AbstractSensor{
    private:
    float R0;
    float alpha;
    float beta;
    float gamma;
    float delta;
    float epsilon;
    float zeta;
    std::vector<float> interpolationTable;
    void createInterpolationTable();
    float simulatePRTResistanceMeasurement(float);
    protected:
    float trasmute(float) const override;

    public:
    TemperaturePRTS();
    TemperaturePRTS(    const std::string name, 
                        const  std::string shortDesc,
                        const  std::string longDesc,
                        const  std::string xAxisLabel,
                        const  unsigned int simulationSpan,
                        const  float sensibility,
                        const  float maxMeasurable,
                        const  float minMeasurable,
                        const float R0,
                        const float alpha,
                        const float beta,
                        const float gamma,
                        const float delta,
                        const float epsilon,
                        const float zeta);

    void accept(VisitorInterface& visitor) override;

    float getR0() const;
    float getAlpha() const;
    float getBeta() const;
    float getGamma() const;
    float getDelta() const;
    float getEpsilon() const;
    float getZeta() const;

    void setR0( float) ;
    void setAlpha( float) ;
    void setBeta( float) ;
    void setGamma( float) ;
    void setDelta( float) ;
    void setEpsilon( float) ;
    void setZeta( float) ;
    
};

}
#endif
