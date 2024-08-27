#ifndef JSON_VISITOR_H
#define JSON_VISITOR_H


#include "ConstVisitorInterface.h"
#include <QJsonObject>
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h"
#include "../sensor/Dust25S.h"

namespace Sensor {

    class JsonVisitor : public ConstVisitorInterface {
    private:
        QJsonObject sensorsRappresentation;
    public:
        const QJsonObject& getsensorsRappresentation() const;
        void visitTemperaturePRTS(const TemperaturePRTS& sensor) override;
        void visitHumidityNTCS(const HumidityNTCS& sensor) override;
        void visitDust25S(const Dust25S& sensor) override;
    };

}
#endif