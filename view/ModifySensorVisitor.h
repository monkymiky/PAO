#ifndef MODIFY_SENSOR_VISITOR_H
#define MODIFY_SENSOR_VISITOR_H

#include "../sensor/visitorInterface.h"
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h" 
#include "../sensor/Dust25S.h"
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <vector>


namespace Sensor {
namespace View{

class ModifySensorVisitor : public VisitorInterface {
private:
    QWidget* parent;
    QFrame* CBframe;
    QComboBox* typeCB;
    QFrame* sensorDataFrame;
    std::unordered_map<std::string, QLineEdit*> dataFields;
    QString * yAxisLabel;

    void addDataField(QString label, QString label2, QFrame* parentFrame, QVBoxLayout* layout);

public:
    ModifySensorVisitor(QWidget* parent);

    QFrame* getCBFrame() const { return CBframe; }  
    QFrame* getSensorDataFrame() const { return sensorDataFrame; }
    std::unordered_map<std::string, QLineEdit*> getDataFields() const { return dataFields; }
    QComboBox* getTypeCB() const { return typeCB; }
    QString* getYAxisLabel() const { return yAxisLabel; }

    void visitTemperaturePRTS(const TemperaturePRTS& sensor) override ;

    void visitHumidityNTCS(const HumidityNTCS& sensor) override ;

    void visitDust25S(const Dust25S& sensor) override ;
};
}
}



#endif // MODIFY_SENSOR_VISITOR_H
