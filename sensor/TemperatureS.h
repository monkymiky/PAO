#ifndef TEMPERATURE_PRT_SENSOR_H
#define TEMPERATURE_PRT_SENSOR_H

#include "AbstractSensor.h"

namespace Sensor{

class TemperaturePRTS : public AbstractSensor{
    private:
    double R0;
    double alpha;
    double beta;
    double gamma;
    double delta;
    double epsilon;
    double zeta;
    std::vector<double> interpolationTable;
    void createInterpolationTable();
    double simulatePRTResistanceMeasurement(double);
    protected:
    double trasmute(double) const override;

    public:
    TemperaturePRTS();
    TemperaturePRTS(    const std::string name, 
                        const  std::string shortDesc,
                        const  std::string longDesc,
                        const  std::string xAxisLabel,
                        const  unsigned int simulationSpan,
                        const  double sensibility,
                        const  double maxMeasurable,
                        const  double minMeasurable,
                        const double R0,
                        const double alpha,
                        const double beta,
                        const double gamma,
                        const double delta,
                        const double epsilon,
                        const double zeta);

    void accept(VisitorInterface& visitor) override;

    double getR0() const;
    double getAlpha() const;
    double getBeta() const;
    double getGamma() const;
    double getDelta() const;
    double getEpsilon() const;
    double getZeta() const;

    void setR0( double) ;
    void setAlpha( double) ;
    void setBeta( double) ;
    void setGamma( double) ;
    void setDelta( double) ;
    void setEpsilon( double) ;
    void setZeta( double) ;
    
};

}
#endif
