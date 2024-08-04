#include "SensorManager.h"
#include "JsonVisitor.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"

namespace Sensor{

    class JsonPharser{
    public:
        static void savetoJson(const SensorManager& manager, const QString& filename){
            QJsonArray sensors;
            for(auto sensor : manager.getSensors()){
                JsonVisitor visitor;
                sensor->accept(visitor);
                sensors.append(visitor.getObject());
            }
            QJsonObject obj;
            obj["sensors"] = sensors;
            QJsonDocument doc(obj);
            QFile file(filename);
            file.open(QIODevice::WriteOnly);
            file.write(doc.toJson());
            file.close();
        }

        static void openfromJson(SensorManager& manager, const QString& filename){
            QFile file(filename);
            file.open(QIODevice::ReadOnly);
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            file.close();
            QJsonArray sensors = doc.object()["sensors"].toArray();
            for(auto sensor : sensors){
                QJsonObject obj = sensor.toObject();
                AbstractSensor* sens;
                if(obj.contains("R0")){
                    const_cast<TemperaturePRTS*>(sens) = new TemperaturePRTS(obj["name"].toString(), obj["shortDesc"].toString(), obj["longDesc"].toString(), obj["xAxisLabel"].toString(), obj["simulationSpan"].toFloat(), obj["sensibility"].toFloat(), obj["maxMeasurable"].toFloat(), obj["minMeasurable"].toFloat(), obj["R0"].toFloat(), obj["alpha"].toFloat(), obj["beta"].toFloat(), obj["gamma"].toFloat(), obj["delta"].toFloat(), obj["epsilon"].toFloat(), obj["zeta"].toFloat());
                    manager.addSensor(sens);
                }else if(obj.contains("AHumid")){
                    const_cast<HumidityNTCS*>(sens) = new HumidityNTCS(obj["name"].toString(), obj["shortDesc"].toString(), obj["longDesc"].toString(), obj["xAxisLabel"].toString(), obj["simulationSpan"].toFloat(), obj["sensibility"].toFloat(), obj["maxMeasurable"].toFloat(), obj["minMeasurable"].toFloat(), obj["AHumid"].toFloat(), obj["BHumid"].toFloat(), obj["CHumid"].toFloat());
                    manager.addSensor(sens);
                }else if(obj.contains("ADust")){
                    const_cast<Dust25S*>(sens) = new Dust25S(obj["name"].toString(), obj["shortDesc"].toString(), obj["longDesc"].toString(), obj["xAxisLabel"].toString(), obj["simulationSpan"].toFloat(), obj["sensibility"].toFloat(), obj["maxMeasurable"].toFloat(), obj["minMeasurable"].toFloat(), obj["ADust"].toFloat(), obj["BDust"].toFloat());
                    manager.addSensor(sens);
                }else{
                    std::cerr << "Sensor type not recognized" << std::endl;
                }
                std::vector<std::array<float, 2>> measure;
                QJsonArray* measureArray = obj["measure"].toArray();
                for(auto pointArray : *measureArray){
                    QJsonArray* point = pointArray.toArray();
                    measure.push_back({point[0].toFloat(), point[1].toFloat()});
                }
                for(auto point : measure){
                    sens->addPoint(point);
                }
            }
        }
    }

}