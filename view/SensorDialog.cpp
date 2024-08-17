#include "SensorDialog.h"
#include <math.h>
#include "../sensor/Dust25S.h"
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h"
#include "ModifySensorVisitor.h"
#include <QtWidgets/QMessageBox>


#include <iostream>

namespace Sensor {
namespace View {

void SensorDialog::addFrame(QString label, QWidget & widget, QLayout& layout){
    QFrame *Frame = new QFrame(this);
    Frame->setFrameShape(QFrame::StyledPanel);
   
    QHBoxLayout *frameLayout = new QHBoxLayout(Frame);
    QLabel *Lab = new QLabel(label, this);
    frameLayout->addWidget(Lab);
    frameLayout->addWidget(&widget);

    layout.addWidget(Frame);
};

SensorDialog::SensorDialog(MainWindow& mainWindow, AbstractSensor *sensor)
    : mainWindow(mainWindow),
    sensor(sensor),
    QDialog(&mainWindow),
    titleLE(QLineEdit(this)),
    shortDescLE(QLineEdit(this)),
    longDescTE(QTextEdit(this)),
    sensibilityLE(QLineEdit(this)),
    spanSimulLE(QLineEdit(this)),
    typeField(new QComboBox(this)),
    maxLE(QLineEdit(this)),
    minLE(QLineEdit(this)),
    
    dustA(QLineEdit(this)),
    dustB(QLineEdit(this)),

    humidA(QLineEdit(this)),
    humidB(QLineEdit(this)),
    humidC(QLineEdit(this)),

    tempR0(QLineEdit(this)),
    tempAlpha(QLineEdit(this)),
    tempBeta(QLineEdit(this)),
    tempGamma(QLineEdit(this)),
    tempDelta(QLineEdit(this)),
    tempEpsilon(QLineEdit(this)),
    tempZeta(QLineEdit(this)),


    tempFrame(QFrame(this)),
    humidFrame(QFrame(this)),
    dustFrame(QFrame(this)),

    addP(new TableButtonItem("+", 2)),
    dataOutFrame(QFrame(this)),

    dataL(QLabel(QString::fromStdString("Misurazioni: "), this)),
    yAxisLabelItem(new QTableWidgetItem("")),
    tableWidget(new QTableWidget(3, 3, this))
    {
    this->setFixedSize(800, 500);
    if(sensor == nullptr) this->setWindowTitle("Aggiungi Sensore");
    else this->setWindowTitle("Modifica Sensore");

    QFrame* scrollFrame = new QFrame();
    QVBoxLayout* mainLayout = new QVBoxLayout(scrollFrame);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setMinimumSize(800, 500);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollFrame);

    if(sensor != nullptr){
        titleLE.setText(QString::fromStdString(sensor->getTitle()));
        shortDescLE.setText(QString::fromStdString(sensor->getShortDescription()));
        longDescTE.setText(QString::fromStdString(sensor->getLongDescription()));
        sensibilityLE.setText(QString::number(sensor->getSensibility()));
        spanSimulLE.setText(QString::number(sensor->getSimulationSpan()));
        maxLE.setText(QString::number(sensor->getMaxMeasurable()));
        minLE.setText(QString::number(sensor->getMinMeasurable()));
    }

    addFrame(QString::fromStdString("Titolo: "), titleLE, *mainLayout);
    addFrame(QString::fromStdString("Descrizione corta: "), shortDescLE, *mainLayout);
    addFrame(QString::fromStdString("Descrizione Lunga: "), longDescTE, *mainLayout);
    addFrame(QString::fromStdString("Sensibilità: "), sensibilityLE, *mainLayout);
    addFrame(QString::fromStdString("Massimo misurabile: "), maxLE, *mainLayout);
    addFrame(QString::fromStdString("Minimo misurabile: "), minLE, *mainLayout);
    addFrame(QString::fromStdString("Intervallo simulazione: "), spanSimulLE, *mainLayout);

    if(sensor != nullptr){
        ModifySensorVisitor visitor(scrollFrame);
        sensor->accept(visitor);
        mainLayout->addWidget(visitor.gettypeFrame());
        mainLayout->addWidget(visitor.getsensorSpec());
        sensorSpecificField = visitor.getsensorSpecificField();
        typeField = visitor.gettypeField();
        yAxisLabelItem->setText(*(visitor.getYAxisLabel()));
    }else{
        typeField->addItem("Temperatura NTP", 0);
        typeField->addItem("Umidità NTC", 1);
        typeField->addItem("Polveri PM 2,5", 2);
        addFrame(QString::fromStdString("Tipo di Sensore: "), *typeField, *mainLayout);

        connect(typeField, SIGNAL(currentIndexChanged(int)), this, SLOT(showType(int)));

        tempFrame.setFrameShape(QFrame::StyledPanel);

        QGridLayout* tempLayout = new QGridLayout(&tempFrame);
        addFrame(QString::fromStdString("R0 : "), tempR0, *tempLayout);
        addFrame(QString::fromStdString("Alpha : "), tempAlpha, *tempLayout);
        addFrame(QString::fromStdString("Beta : "), tempBeta, *tempLayout);
        addFrame(QString::fromStdString("Gamma : "), tempGamma, *tempLayout);
        addFrame(QString::fromStdString("Delta : "), tempDelta, *tempLayout);
        addFrame(QString::fromStdString("Epsilon : "), tempEpsilon, *tempLayout);
        addFrame(QString::fromStdString("Zeta : "), tempZeta, *tempLayout);

        mainLayout->addWidget(&tempFrame);
        tempFrame.hide();

        humidFrame.setFrameShape(QFrame::StyledPanel);

        QGridLayout* humidLayout = new QGridLayout(&humidFrame);
        addFrame(QString::fromStdString("A : "), humidA, *humidLayout);
        addFrame(QString::fromStdString("B : "), humidB, *humidLayout);
        addFrame(QString::fromStdString("C : "), humidC, *humidLayout);

        mainLayout->addWidget(&humidFrame);
        humidFrame.hide();

        dustFrame.setFrameShape(QFrame::StyledPanel);

        QGridLayout* dustLayout = new QGridLayout(&dustFrame);
        addFrame(QString::fromStdString("A : "), dustA, *dustLayout);
        addFrame(QString::fromStdString("B : "), dustB, *dustLayout);

        mainLayout->addWidget(&dustFrame);
        dustFrame.hide();
    }

    mainLayout->addWidget(&dataL);
    
    dataOutFrame.setFrameShape(QFrame::StyledPanel);
    dataOutFrame.setFixedHeight(155);
    QHBoxLayout* dataOutFrameLayout = new QHBoxLayout(&dataOutFrame);
    mainLayout->addWidget(&dataOutFrame);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            tableWidget->setItem(row, col, item);
        }
    }
    
    QTableWidgetItem* emptyItem = new QTableWidgetItem();
    emptyItem->setFlags(emptyItem->flags() ^ Qt::ItemIsEditable); // toggle the possibility to edit the cell
    tableWidget->setItem(0, 0, emptyItem);

    QTableWidgetItem* axisTitleItem = new QTableWidgetItem("Misura");
    axisTitleItem->setFlags(axisTitleItem->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 1, axisTitleItem);
    
    QTableWidgetItem* yAxisItem = new QTableWidgetItem("Asse Y");
    yAxisItem->setFlags(yAxisItem->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 0, yAxisItem);

    yAxisLabelItem->setFlags(yAxisLabelItem->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 1, yAxisLabelItem);
    
    QTableWidgetItem* xAxisItem = new QTableWidgetItem("Asse X");
    xAxisItem->setFlags(xAxisItem->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(2, 0, xAxisItem);

    QTableWidgetItem* xAxisTitleItem = new QTableWidgetItem();
    if(sensor != nullptr){
         xAxisTitleItem->setText(QString::fromStdString(sensor->getXAxisLabel()));
    }
    tableWidget->setItem(2, 1, xAxisTitleItem);
    
    // Set button with "+" text in row 0, column 2 rowspan 3 and columnspan 1
    tableWidget->setCellWidget(0, 2, addP);
    addP->setStyleSheet("background-color: green");
    connect(addP, SIGNAL(clicked()), this, SLOT(addPoint()));
    tableWidget->setSpan(0, 2, 3, 1);
    if(sensor != nullptr){
        for (int i = 0; i < sensor->getMeasure().size(); i++)
        {
            tableWidget->insertColumn(i+2);
            QTableWidgetItem* yItem = new QTableWidgetItem(QString::number(sensor->getMeasure()[i][0]));
            tableWidget->setItem(1, i+2, yItem);
            QTableWidgetItem* xItem = new QTableWidgetItem(QString::number(sensor->getMeasure()[i][1]));
            tableWidget->setItem(2, i+2, xItem);
            TableButtonItem* removeButton = new TableButtonItem("x",i+2, tableWidget);
            removeButton->setStyleSheet("background-color: red");
            tableWidget->setCellWidget(0, i+2, removeButton);
            connect(removeButton, SIGNAL(clicked()), this, SLOT(removeColumn()));
        }
    }
    dataOutFrameLayout->addWidget(tableWidget);
    if(sensor == nullptr){
        dataOutFrame.hide();
    }

    QFrame* save_disc_Frame = new QFrame(scrollFrame);
    QHBoxLayout* save_disc_Layout = new QHBoxLayout(save_disc_Frame);
    mainLayout->addWidget(save_disc_Frame);

    QPushButton * discard = new QPushButton("Annulla", save_disc_Frame);
    save_disc_Layout->addWidget(discard);
    save_disc_Layout->addStretch();
    QPushButton * save = new QPushButton("Salva", save_disc_Frame);
    save_disc_Layout->addWidget(save);

    connect(discard, SIGNAL(clicked()), this,SLOT( close()));
    connect(save, SIGNAL(clicked()), this,SLOT(saveSensor()));
};

void SensorDialog::saveSensor(){

    std::string title = titleLE.text().toStdString();
    std::string shortDescription = shortDescLE.text().toStdString();
    std::string longDescription = longDescTE.toPlainText().toStdString();
    std::string xAxisLabel = tableWidget->item(2,1)->text().toStdString();
    
    unsigned int simulationSpan = spanSimulLE.text().toUInt();
    double sensibility = sensibilityLE.text().toDouble();
    double maxMeasurable = maxLE.text().toDouble();
    double minMeasurable = minLE.text().toDouble();

    if(title.empty() || shortDescription.empty() || longDescription.empty() || xAxisLabel.empty()){
        QMessageBox::warning(this, "Avviso:", "Tutti i campi devono essere compilati");
        return;
    }

    int sw = typeField->currentIndex();
    if(sensor == nullptr){
        if(sw == 0){
            double r0 = tempR0.text().toDouble();
            double alpha = tempAlpha.text().toDouble();
            double beta = tempBeta.text().toDouble();
            double gamma = tempGamma.text().toDouble();
            double delta = tempDelta.text().toDouble();
            double epsilon = tempEpsilon.text().toDouble();
            double zeta = tempZeta.text().toDouble();

            if(r0 == 0 || alpha == 0 || beta == 0 || gamma == 0 || delta == 0 || epsilon == 0 || zeta == 0){
                QMessageBox::warning(this, "Avviso:", "Tutti i campi devono essere compilati");
                return;
            }

            sensor = new TemperaturePRTS(
                title,shortDescription,longDescription,xAxisLabel,simulationSpan,
                sensibility,maxMeasurable,minMeasurable,r0,alpha,beta,gamma,delta,
                epsilon,zeta);
        }else if (sw == 1){
            double Ah = humidA.text().toDouble();
            double Bh = humidB.text().toDouble();
            double Ch = humidC.text().toDouble();
            
            if(Ah == 0 || Bh == 0 || Ch == 0){
                QMessageBox::warning(this, "Avviso:", "Tutti i campi devono essere compilati");
                return;
            }

            sensor = new HumidityNTCS(
                title,shortDescription,longDescription,
                xAxisLabel,simulationSpan,sensibility,maxMeasurable,minMeasurable,
                Ah,Bh,Ch
            );
        }else if(sw == 2){
            double Ad = dustA.text().toDouble();
            double Bd = dustB.text().toDouble();

            if(Ad == 0 || Bd == 0){
                QMessageBox::warning(this, "Avviso:", "Tutti i campi devono essere compilati");
                return;
            }
                
            sensor = new Dust25S(
                title,shortDescription,longDescription,xAxisLabel,simulationSpan,
                sensibility,maxMeasurable,minMeasurable,Ad,Bd);
        }else {
            std::cerr << "Unexpected sensor type selected in SensorDialog::save()";
        }
        mainWindow.addSensor(sensor);
    }else{
        sensor->setTitle(title);
        sensor->setShortDescription(shortDescription);
        sensor->setLongDescription(longDescription);
        sensor->setXAxisLabel(xAxisLabel);
        sensor->setSimulationSpan(simulationSpan);
        sensor->setSensibility(sensibility);
        sensor->setMaxMeasurable(maxMeasurable);
        sensor->setMinMeasurable(minMeasurable);

        if(sw == 0){
            double r0 = sensorSpecificField["R0"]->text().toDouble();
            double alpha = sensorSpecificField["Alpha"]->text().toDouble();
            double beta = sensorSpecificField["Beta"]->text().toDouble();
            double gamma = sensorSpecificField["Gamma"]->text().toDouble();
            double delta = sensorSpecificField["Delta"]->text().toDouble();
            double epsilon = sensorSpecificField["Epsilon"]->text().toDouble();
            double zeta = sensorSpecificField["Zeta"]->text().toDouble();

            if(auto tempSensor = dynamic_cast<TemperaturePRTS*>(sensor)){
                tempSensor->setR0(r0);
                tempSensor->setAlpha(alpha);
                tempSensor->setBeta(beta);
                tempSensor->setGamma(gamma);
                tempSensor->setDelta(delta);
                tempSensor->setEpsilon(epsilon);
                tempSensor->setZeta(zeta);
            }
        }
        else if(sw == 1){
            double Ah = sensorSpecificField["A"]->text().toDouble();
            double Bh = sensorSpecificField["B"]->text().toDouble();
            double Ch = sensorSpecificField["C"]->text().toDouble();
            if(auto humidSensor = dynamic_cast<HumidityNTCS*>(sensor)){
                humidSensor->setA(Ah);
                humidSensor->setB(Bh);
                humidSensor->setC(Ch);
            }
        }
        else if(sw == 2){
            double Ad = sensorSpecificField["A"]->text().toDouble();
            double Bd = sensorSpecificField["B"]->text().toDouble();
            if(auto dustSensor = dynamic_cast<Dust25S*>(sensor)){
                dustSensor->setA(Ad);
                dustSensor->setB(Bd);
            }
        }
        else {
            std::cerr << "Unexpected sensor type selected in SensorDialog::save()";
        }
        sensor->clearPoints();  
    }

    for (int column = 2; column < tableWidget->columnCount()-1; column++) {
            QTableWidgetItem* yItem = tableWidget->item(1, column);
            QTableWidgetItem* xItem = tableWidget->item(2, column);
            if (yItem && xItem) {
                double y = yItem->text().toDouble();
                double x = xItem->text().toDouble();
                std::array<double, 2> p = {y, x};
                sensor->addPoint(p);
            }
        }
    close();
};

void SensorDialog::showType(int index){
    tempFrame.hide();
    humidFrame.hide();
    dustFrame.hide();
    switch(index){
        case 0:
            tempFrame.show();
            yAxisLabelItem->setText("Temperatura [°C]");
            dataL.show();
            dataOutFrame.show();
            break;
        case 1:
            humidFrame.show();
            yAxisLabelItem->setText("Umidità [%]");
            dataL.show();
            dataOutFrame.show();
            break;
        case 2:
            dustFrame.show();
            yAxisLabelItem->setText("Polveri [µg/m³]");
            dataL.show();
            dataOutFrame.show();
            break;
        default:
            std::cerr << "Unexpected sensor type selected in SensorDialog::showType()";
    }
}

void SensorDialog::addPoint(){
    int columnCount = tableWidget->columnCount();
    tableWidget->insertColumn(columnCount-1);

    for (int row = 1; row < tableWidget->rowCount(); row++) {
        QTableWidgetItem* item = new QTableWidgetItem();
        tableWidget->setItem(row, columnCount-1, item);
    }

    TableButtonItem* removeButton = new TableButtonItem("x",columnCount-1, tableWidget);
    removeButton->setStyleSheet("background-color: red");
    tableWidget->setCellWidget(0, columnCount-1, removeButton);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeColumn()));
    addP->setPositionIndex(columnCount);
}

void SensorDialog::removeColumn(){
    TableButtonItem* removeButton = dynamic_cast<TableButtonItem*>(sender()); // qt dynamic cast
    if (removeButton) {
        int column = removeButton->getIndex();
        tableWidget->removeColumn(column);
    }
    // update index of all remove buttons
    for (int i = 2; i < tableWidget->columnCount(); i++) {
        TableButtonItem* removeButton = dynamic_cast<TableButtonItem*>(tableWidget->cellWidget(0, i));
        if (removeButton) {
            removeButton->setIndex(i);
        }
    }
    addP->setPositionIndex(tableWidget->columnCount());
}



}
}
