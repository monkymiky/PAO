#include "VisitorInterface.h"
#include <QJsonObject>


namespace Sensor {

    class JsonVisitor : public VisitorInterface {
    private:
        QJsonObject object;
    public:
        const QJsonObject& getObject() const;
        void visitTemperaturePRTS(const TemperaturePRTS& sensor) override;
        void visitHumidityNTCS(const HumidityNTCS& sensor) override;
        void visitDust25S(const Dust25S& sensor) override;
    };

}