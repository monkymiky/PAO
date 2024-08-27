#include "ModifySensorVisitor.h"

namespace Sensor {
    namespace View {

        void ModifySensorVisitor::addDataField(
            const QString& label, const QString& label2, QFrame* parentFrame,  QVBoxLayout* layout
            ){
            QFrame* frame = new QFrame(parentFrame);
            QHBoxLayout *frameLayout = new QHBoxLayout(frame);
            QLabel *Lab = new QLabel(label,frame);
            frameLayout->addWidget(Lab);
            QLineEdit* lineEdit2 = new QLineEdit(label2, frame);
            frameLayout->addWidget(lineEdit2);
            layout->addWidget(frame);
            sensorSpecificField[label.toStdString()] = lineEdit2;
        }

        ModifySensorVisitor::ModifySensorVisitor(QWidget* parent) : 
        parent(parent), typeFrame(new QFrame(parent)), 
        typeField(new QComboBox(parent)), sensorSpec(new QFrame(parent))
        {}

        void ModifySensorVisitor::visitTemperaturePRTS(const TemperaturePRTS& sensor) {
        typeField->addItem("Temperatura NTP", 0);
        typeField->addItem("Umidità NTC", 1);
        typeField->addItem("Polveri PM 2,5", 2);
        typeField->setCurrentIndex(0); // Set the combobox to "Temperatura NTP"
        yAxisLabel = new QString("Temperatura [°C]");

        typeFrame->setFrameShape(QFrame::StyledPanel);
        typeFrame->setVisible(false);

        QHBoxLayout *frameLayout = new QHBoxLayout(typeFrame);
        QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),typeFrame);
        frameLayout->addWidget(Lab);
        frameLayout->addWidget(typeField);
        
        sensorSpec->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* tempLayout = new QVBoxLayout(sensorSpec);

        addDataField(QString::fromStdString("R0"),QString::number(sensor.getR0()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Alpha"),QString::number(sensor.getAlpha()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Beta"),QString::number(sensor.getBeta()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Gamma"),QString::number(sensor.getGamma()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Delta"),QString::number(sensor.getDelta()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Epsilon"),QString::number(sensor.getEpsilon()) , sensorSpec, tempLayout);
        addDataField(QString::fromStdString("Zeta"),QString::number(sensor.getZeta()) , sensorSpec, tempLayout);
        }
        
        void ModifySensorVisitor::visitHumidityNTCS(const HumidityNTCS& sensor) {
            typeField->addItem("Temperatura NTP", 0);
            typeField->addItem("Umidità NTC", 1);
            typeField->addItem("Polveri PM 2,5", 2);
            typeField->setCurrentIndex(1); // Set the combobox to "Umidità NTC"
            yAxisLabel = new QString("Umidità [%]");
            

            typeFrame->setFrameShape(QFrame::StyledPanel);
            typeFrame->setVisible(false);

            QHBoxLayout *frameLayout = new QHBoxLayout(typeFrame);
            QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),typeFrame);
            frameLayout->addWidget(Lab);
            frameLayout->addWidget(typeField);
            
            sensorSpec->setFrameShape(QFrame::StyledPanel);
            QVBoxLayout* humidLayout = new QVBoxLayout(sensorSpec);

            addDataField(QString::fromStdString("A"),QString::number(sensor.getA()) , sensorSpec, humidLayout);
            addDataField(QString::fromStdString("B"),QString::number(sensor.getB()) , sensorSpec, humidLayout);
            addDataField(QString::fromStdString("C"),QString::number(sensor.getC()) , sensorSpec, humidLayout);
        }

        void ModifySensorVisitor::visitDust25S(const Dust25S& sensor){
        typeField->addItem("Temperatura NTP", 0);
        typeField->addItem("Umidità NTC", 1);
        typeField->addItem("Polveri PM 2,5", 2);
        typeField->setCurrentIndex(2); // Set the combobox to "Polveri PM 2,5"
        yAxisLabel = new QString("Polveri PM 2,5 [mg/m^3]");

        typeFrame->setFrameShape(QFrame::StyledPanel);
        typeFrame->setVisible(false);
        QHBoxLayout *frameLayout = new QHBoxLayout(typeFrame);
        QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),typeFrame);
        frameLayout->addWidget(Lab);
        frameLayout->addWidget(typeField);

        sensorSpec->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* dustLayout = new QVBoxLayout(sensorSpec);

        addDataField(QString::fromStdString("A"),QString::number(sensor.getA()) , sensorSpec, dustLayout);
        addDataField(QString::fromStdString("B"),QString::number(sensor.getB()) , sensorSpec, dustLayout);
    }

    QFrame* ModifySensorVisitor::gettypeFrame() const { return typeFrame; }  
    QFrame* ModifySensorVisitor::getsensorSpec() const { return sensorSpec; }
    std::unordered_map<std::string, QLineEdit*> ModifySensorVisitor::getsensorSpecificField() const { return sensorSpecificField; }
    QComboBox* ModifySensorVisitor::gettypeField() const { return typeField; }
    QString* ModifySensorVisitor::getYAxisLabel() const { return yAxisLabel; }
} 
}
