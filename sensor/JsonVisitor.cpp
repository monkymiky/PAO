#include "JsonVisitor.h"
#include <QJsonArray>


namespace Sensor {

    const QJsonObject& JsonVisitor::getObject() const {
        return object;
    }

    void JsonVisitor::visitTemperaturePRTS(const TemperaturePRTS& sensor) {
        QJsonObject obj;
        obj["name"] = sensor.getName();
        obj["shortDesc"] = sensor.getShortDesc();
        obj["longDesc"] = sensor.getLongDesc();
        obj["xAxisLabel"] = sensor.getXAxisLabel();
        obj["simulationSpan"] = sensor.getSimulationSpan();
        obj["sensibility"] = sensor.getSensibility();
        obj["maxMeasurable"] = sensor.getMaxMeasurable();
        obj["minMeasurable"] = sensor.getMinMeasurable();
        obj["R0"] = sensor.getR0();
        obj["alpha"] = sensor.getAlpha();
        obj["beta"] = sensor.getBeta();
        obj["gamma"] = sensor.getGamma();
        obj["delta"] = sensor.getDelta();
        obj["epsilon"] = sensor.getEpsilon();
        obj["zeta"] = sensor.getZeta();

        QJsonArray data;
        for (const auto& point : sensor.getMeasure()) {
        data.append(point);
        }
        obj["measure"] = data;
        object = obj;
    }

    void JsonVisitor::visitHumidityNTCS(const HumidityNTCS& sensor) {
        QJsonObject obj;
        
        obj["name"] = sensor.getName();
        obj["shortDesc"] = sensor.getShortDesc();
        obj["longDesc"] = sensor.getLongDesc();
        obj["xAxisLabel"] = sensor.getXAxisLabel();
        obj["simulationSpan"] = sensor.getSimulationSpan();
        obj["sensibility"] = sensor.getSensibility();
        obj["maxMeasurable"] = sensor.getMaxMeasurable();
        obj["minMeasurable"] = sensor.getMinMeasurable();
        obj["AHumid"] = sensor.getA();
        obj["BHumid"] = sensor.getB();
        obj["CHumid"] = sensor.getC();

        QJsonArray data;
        for (const auto& point : sensor.getMeasure()) {
        data.append(point);
        }
        obj["measure"] = data;
        
        object = obj;
    }

    void JsonVisitor::visitDust25S(const Dust25S& sensor) {
        QJsonObject obj;
        
        obj["name"] = sensor.getName();
        obj["shortDesc"] = sensor.getShortDesc();
        obj["longDesc"] = sensor.getLongDesc();
        obj["xAxisLabel"] = sensor.getXAxisLabel();
        obj["simulationSpan"] = sensor.getSimulationSpan();
        obj["sensibility"] = sensor.getSensibility();
        obj["maxMeasurable"] = sensor.getMaxMeasurable();
        obj["minMeasurable"] = sensor.getMinMeasurable();
        obj["ADust"] = sensor.getA();
        obj["BDust"] = sensor.getB();

        QJsonArray data;
        for (const auto& point : sensor.getMeasure()) {
        data.append(point);
        }
        obj["measure"] = data;

        object = obj;
    }

}