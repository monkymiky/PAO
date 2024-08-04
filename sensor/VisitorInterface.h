#ifndef VISITOR_INTERFACE_H
#define VISITOR_INTERFACE_H
namespace Sensor {


class Dust25S;
class TemperaturePRTS;
class HumidityNTCS;



class VisitorInterface {
  public:
    virtual ~VisitorInterface() {};
    virtual void visitTemperaturePRTS(const TemperaturePRTS& TemperaturePRT) = 0;
    virtual void visitHumidityNTCS(const HumidityNTCS& Humidity) = 0;
    virtual void visitDust25S(const Dust25S& Dust25) = 0;
};
}

#endif
