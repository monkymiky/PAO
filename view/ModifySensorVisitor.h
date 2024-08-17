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
    QFrame* typeFrame;
    QComboBox* typeField;
    QFrame* sensorSpec;
    std::unordered_map<std::string, QLineEdit*> sensorSpecificField;
    QString * yAxisLabel;

    void addDataField(QString label, QString label2, QFrame* parentFrame, QVBoxLayout* layout);

public:
    ModifySensorVisitor(QWidget* parent);ù

    QFrame* gettypeFrame() const ;
    QFrame* getsensorSpec() const ;
    std::unordered_map<std::string, QLineEdit*> getsensorSpecificField() const ;
    QComboBox* gettypeField() const ;
    QString* getYAxisLabel() const ;

    void visitTemperaturePRTS(const TemperaturePRTS& sensor) override ;

    void visitHumidityNTCS(const HumidityNTCS& sensor) override ;

    void visitDust25S(const Dust25S& sensor) override ;
};
}
}



#endif // MODIFY_SENSOR_VISITOR_H
