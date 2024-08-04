#include "ModifySensorVisitor.h"

namespace Sensor {
    namespace View {

        void ModifySensorVisitor::addDataField(QString label, QString label2, QFrame* parentFrame, QVBoxLayout* layout){
            QFrame* Frame = new QFrame(parentFrame);
            QHBoxLayout *frameLayout = new QHBoxLayout(Frame);
            QLabel *Lab = new QLabel(label,Frame);
            frameLayout->addWidget(Lab);
            QLineEdit* lineEdit2 = new QLineEdit(label2, Frame);
            frameLayout->addWidget(lineEdit2);
            layout->addWidget(Frame);
            dataFields[label.toStdString()] = lineEdit2;
        }

        ModifySensorVisitor::ModifySensorVisitor(QWidget* parent) : 
        parent(parent), CBframe(new QFrame(parent)), 
        typeCB(new QComboBox(parent)), sensorDataFrame(new QFrame(parent))
        {}

        void ModifySensorVisitor::visitTemperaturePRTS(const TemperaturePRTS& sensor) {
        typeCB->addItem("Temperatura NTP", 0);
        typeCB->addItem("Umidità NTC", 1);
        typeCB->addItem("Polveri PM 2,5", 2);
        typeCB->setCurrentIndex(0); // Set the combobox to "Temperatura NTP"
        yAxisLabel = new QString("Temperatura [°C]");

        CBframe->setFrameShape(QFrame::StyledPanel);
        CBframe->setVisible(false);

        QHBoxLayout *frameLayout = new QHBoxLayout(CBframe);
        QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),CBframe);
        frameLayout->addWidget(Lab);
        frameLayout->addWidget(typeCB);
        
        sensorDataFrame->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* tempLayout = new QVBoxLayout(sensorDataFrame);

        addDataField(QString::fromStdString("R0"),QString::number(sensor.getR0()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Alpha"),QString::number(sensor.getAlpha()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Beta"),QString::number(sensor.getBeta()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Gamma"),QString::number(sensor.getGamma()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Delta"),QString::number(sensor.getDelta()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Epsilon"),QString::number(sensor.getEpsilon()) , sensorDataFrame, tempLayout);
        addDataField(QString::fromStdString("Zeta"),QString::number(sensor.getZeta()) , sensorDataFrame, tempLayout);
        }
        
        void ModifySensorVisitor::visitHumidityNTCS(const HumidityNTCS& sensor) {
            typeCB->addItem("Temperatura NTP", 0);
            typeCB->addItem("Umidità NTC", 1);
            typeCB->addItem("Polveri PM 2,5", 2);
            typeCB->setCurrentIndex(1); // Set the combobox to "Umidità NTC"
            yAxisLabel = new QString("Umidità [%]");
            

            CBframe->setFrameShape(QFrame::StyledPanel);
            CBframe->setVisible(false);

            QHBoxLayout *frameLayout = new QHBoxLayout(CBframe);
            QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),CBframe);
            frameLayout->addWidget(Lab);
            frameLayout->addWidget(typeCB);
            
            sensorDataFrame->setFrameShape(QFrame::StyledPanel);
            QVBoxLayout* humidLayout = new QVBoxLayout(sensorDataFrame);

            addDataField(QString::fromStdString("A"),QString::number(sensor.getA()) , sensorDataFrame, humidLayout);
            addDataField(QString::fromStdString("B"),QString::number(sensor.getB()) , sensorDataFrame, humidLayout);
            addDataField(QString::fromStdString("C"),QString::number(sensor.getC()) , sensorDataFrame, humidLayout);
        }

        void ModifySensorVisitor::visitDust25S(const Dust25S& sensor){
        typeCB->addItem("Temperatura NTP", 0);
        typeCB->addItem("Umidità NTC", 1);
        typeCB->addItem("Polveri PM 2,5", 2);
        typeCB->setCurrentIndex(2); // Set the combobox to "Polveri PM 2,5"
        yAxisLabel = new QString("Polveri PM 2,5 [mg/m^3]");

        CBframe->setFrameShape(QFrame::StyledPanel);
        CBframe->setVisible(false);
        QHBoxLayout *frameLayout = new QHBoxLayout(CBframe);
        QLabel *Lab = new QLabel(QString::fromStdString("Tipo di Sensore: "),CBframe);
        frameLayout->addWidget(Lab);
        frameLayout->addWidget(typeCB);

        sensorDataFrame->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* dustLayout = new QVBoxLayout(sensorDataFrame);

        addDataField(QString::fromStdString("A"),QString::number(sensor.getA()) , sensorDataFrame, dustLayout);
        addDataField(QString::fromStdString("B"),QString::number(sensor.getB()) , sensorDataFrame, dustLayout);
    }
} 
}
