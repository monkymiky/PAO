#include "JsonVisitor.h"
#include <QJsonArray>
#include <QString>
#include <iostream>


namespace Sensor {

    const QJsonObject& JsonVisitor::getsensorsRappresentation() const {
        return sensorsRappresentation;
    }

    void JsonVisitor::visitTemperaturePRTS(const TemperaturePRTS& sensor) {
        QJsonObject obj;
        obj["name"] = QJsonValue::fromVariant( QString::fromStdString(sensor.getTitle()));
        obj["shortDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getShortDescription()));
        obj["longDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getLongDescription()));
        obj["xAxisLabel"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getXAxisLabel()));
        obj["simulationSpan"] = QJsonValue::fromVariant(QString::number(sensor.getSimulationSpan()));
        std::cerr << "simulationSpan: " << sensor.getSimulationSpan() << std::endl;
        std::cerr << "maxMeasurable: " << sensor.getMaxMeasurable() << std::endl;
        obj["sensibility"] = QJsonValue::fromVariant(QString::number(sensor.getSensibility()));
        obj["maxMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMaxMeasurable()));
        obj["minMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMinMeasurable()));
        obj["R0"] = QJsonValue::fromVariant(QString::number(sensor.getR0()));
        obj["alpha"] = QJsonValue::fromVariant(QString::number(sensor.getAlpha()));
        obj["beta"] = QJsonValue::fromVariant(QString::number(sensor.getBeta()));
        obj["gamma"] = QJsonValue::fromVariant(QString::number(sensor.getGamma()));
        obj["delta"] = QJsonValue::fromVariant(QString::number(sensor.getDelta()));
        obj["epsilon"] = QJsonValue::fromVariant(QString::number(sensor.getEpsilon()));
        obj["zeta"] = QJsonValue::fromVariant(QString::number(sensor.getZeta()));

        QJsonArray data;
        for (const auto point : sensor.getMeasure()) {
        QJsonArray pointArray;
        pointArray.append(QJsonValue::fromVariant(point[0]));
        pointArray.append(QJsonValue::fromVariant(point[1]));
        data.append(pointArray);
        }
        obj["measure"] = data;
        sensorsRappresentation = obj;
    }

    void JsonVisitor::visitHumidityNTCS(const HumidityNTCS& sensor) {
        QJsonObject obj;
        
        obj["name"] = QJsonValue::fromVariant( QString::fromStdString(sensor.getTitle()));
        obj["shortDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getShortDescription()));
        obj["longDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getLongDescription()));
        obj["xAxisLabel"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getXAxisLabel()));
        obj["simulationSpan"] = QJsonValue::fromVariant(QString::number(sensor.getSimulationSpan()));
        obj["sensibility"] = QJsonValue::fromVariant(QString::number(sensor.getSensibility()));
        obj["maxMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMaxMeasurable()));
        obj["minMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMinMeasurable()));
        obj["AHumid"] = QJsonValue::fromVariant(QString::number(sensor.getA()));
        obj["BHumid"] = QJsonValue::fromVariant(QString::number(sensor.getB()));
        obj["CHumid"] = QJsonValue::fromVariant(QString::number(sensor.getC()));

        QJsonArray data;
        for (const auto point : sensor.getMeasure()) {
        QJsonArray pointArray;
        pointArray.append(QJsonValue::fromVariant(point[0]));
        pointArray.append(QJsonValue::fromVariant(point[1]));
        data.append(pointArray);
        }

        obj["measure"] = data;
        
        sensorsRappresentation = obj;
    }

    void JsonVisitor::visitDust25S(const Dust25S& sensor) {
        QJsonObject obj;
        
        obj["name"] = QJsonValue::fromVariant( QString::fromStdString(sensor.getTitle()));
        obj["shortDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getShortDescription()));
        obj["longDesc"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getLongDescription()));
        obj["xAxisLabel"] = QJsonValue::fromVariant(QString::fromStdString(sensor.getXAxisLabel()));
        std::cerr << "simulationSpan: " << sensor.getSimulationSpan() << std::endl;
        std::cerr << "maxMeasurable: " << sensor.getMaxMeasurable() << std::endl;
        
        obj["simulationSpan"] = QJsonValue::fromVariant(QString::number(sensor.getSimulationSpan()));
        obj["sensibility"] = QJsonValue::fromVariant(QString::number(sensor.getSensibility()));
        obj["maxMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMaxMeasurable()));
        obj["minMeasurable"] = QJsonValue::fromVariant(QString::number(sensor.getMinMeasurable()));
        obj["ADust"] = QJsonValue::fromVariant(QString::number(sensor.getA()));
        obj["BDust"] = QJsonValue::fromVariant(QString::number(sensor.getB()));
        
        QJsonArray data;
        for (const auto point : sensor.getMeasure()) {
        QJsonArray pointArray;
        pointArray.append(QJsonValue::fromVariant(point[0]));
        pointArray.append(QJsonValue::fromVariant(point[1]));
        data.append(pointArray);
        }
        
        obj["measure"] = data;

        sensorsRappresentation = obj;
    }

}
