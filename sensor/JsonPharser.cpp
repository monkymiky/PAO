#include "JsonPharser.h"
#include "../view/SensorSmallView.h"
#include <QtWidgets/QMessageBox>


namespace Sensor{
    void JsonPharser::savetoJson(const SensorManager& manager, const QString& filename){
            QJsonArray sensors;
            for(auto sensor : manager.getSensors()){
                JsonVisitor visitor;
                sensor->accept(visitor);
                sensors.append(visitor.getsensorsRappresentation());
            }
            QJsonObject obj;
            obj["sensors"] = sensors;
            QJsonDocument doc(obj);
            QFile file(filename);
            file.open(QIODevice::WriteOnly);
            file.write(doc.toJson());
            file.close();
        }


   void JsonPharser::openfromJson(
    SensorManager& manager,View::Aside& aside,  View::MainWindow* mainWindow, const QString& filename){
        QFile file(filename);
            file.open(QIODevice::ReadOnly);
            QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
            file.close();
            QJsonArray sensors(doc.object()["sensors"].toArray());
            for(auto sensor : sensors){
                QJsonObject obj = sensor.toObject();
                AbstractSensor* sens = nullptr;
                if(obj.contains("R0")){
                    sens = new TemperaturePRTS(
                        obj["name"].toString().toStdString(), 
                        obj["shortDesc"].toString().toStdString(), 
                        obj["longDesc"].toString().toStdString(), 
                        obj["xAxisLabel"].toString().toStdString(), 
                        static_cast<unsigned int>(obj["simulationSpan"].toString().toDouble()), 
                        obj["sensibility"].toString().toDouble(), 
                        obj["maxMeasurable"].toString().toDouble(), 
                        obj["minMeasurable"].toString().toDouble(), 
                        obj["R0"].toString().toDouble(), 
                        obj["alpha"].toString().toDouble(), 
                        obj["beta"].toString().toDouble(), 
                        obj["gamma"].toString().toDouble(), 
                        obj["delta"].toString().toDouble(), 
                        obj["epsilon"].toString().toDouble(), 
                        obj["zeta"].toString().toDouble()
                        );
                    manager.addSensor(sens);
                }else if(obj.contains("AHumid")){
                    sens = new HumidityNTCS(
                        obj["name"].toString().toStdString(),
                        obj["shortDesc"].toString().toStdString(),
                        obj["longDesc"].toString().toStdString(), 
                        obj["xAxisLabel"].toString().toStdString(), 
                        static_cast<unsigned int>(obj["simulationSpan"].toString().toDouble()), 
                        obj["sensibility"].toString().toDouble(), 
                        obj["maxMeasurable"].toString().toDouble(), 
                        obj["minMeasurable"].toString().toDouble(), 
                        obj["AHumid"].toString().toDouble(), 
                        obj["BHumid"].toString().toDouble(), 
                        obj["CHumid"].toString().toDouble()
                        );
                    manager.addSensor(sens);
                }else if(obj.contains("ADust")){
                    sens = new Dust25S(
                        obj["name"].toString().toStdString(), 
                        obj["shortDesc"].toString().toStdString(), 
                        obj["longDesc"].toString().toStdString(), 
                        obj["xAxisLabel"].toString().toStdString(), 
                        static_cast<unsigned int>(obj["simulationSpan"].toString().toDouble()), 
                        obj["sensibility"].toString().toDouble(), 
                        obj["maxMeasurable"].toString().toDouble(), 
                        obj["minMeasurable"].toString().toDouble(), 
                        obj["ADust"].toString().toDouble(), 
                        obj["BDust"].toString().toDouble()
                        );
                    manager.addSensor(sens);
                }else{
                    std::cerr << "Sensor type not recognized" << std::endl;
                }
                if(sens) aside.addSSV(new View::SmallSensorView(*sens, *mainWindow));
                std::vector<std::array<double, 2>> measure;
                QJsonArray measureArray (obj["measure"].toArray());
                for(auto pointArray : measureArray){
                    QJsonArray point(pointArray.toArray());
                    measure.push_back({point[0].toDouble(), point[1].toDouble()});
                }
                for(auto point : measure){
                    try{
                        sens->addPoint(point);
                    }catch(Sensor::DuplicatedXValueException){
                        QMessageBox::warning(mainWindow, "Errore:", "Sono stati rilevati valori duplicati sull asse X, essi non sono ammessi. Un sensore non verrà aperto.");
                        manager.removeSensor(sens);
                        return;
                    }
                }
            }
    }

}
