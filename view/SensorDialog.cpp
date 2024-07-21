#include "SensorDialog.h"
#include <math.h>
#include "../sensor/Dust25S.h"
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h"



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

SensorDialog::SensorDialog(SensorManager& manager, QWidget* parent)
    : manager(manager),
      QDialog(parent),
      titleLE(QLineEdit(this)),
      shortDescLE(QLineEdit(this)),
      longDescTE(QTextEdit(this)),
      sensibilityLE(QLineEdit(this)),
      spanSimulLE(QLineEdit(this)),
      typeCB(QComboBox(this)),
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
    this->setWindowTitle("Aggiungi Sensore");

    QFrame* ScrollFrame = new QFrame();
    QVBoxLayout* mainLayout = new QVBoxLayout(ScrollFrame);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setMinimumSize(800, 500);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(ScrollFrame);

    addFrame(QString::fromStdString("Titolo: "), titleLE, *mainLayout);
    addFrame(QString::fromStdString("Descrizione corta: "), shortDescLE, *mainLayout);
    addFrame(QString::fromStdString("Descrizione Lunga: "), longDescTE, *mainLayout);
    addFrame(QString::fromStdString("Sensibilità: "), sensibilityLE, *mainLayout);
    addFrame(QString::fromStdString("Massimo misurabile: "), maxLE, *mainLayout);
    addFrame(QString::fromStdString("Minimo misurabile: "), minLE, *mainLayout);
    addFrame(QString::fromStdString("Intervallo simulazione: "), spanSimulLE, *mainLayout);

    typeCB.addItem("Temperatura NTP", 0);
    typeCB.addItem("Umidità NTC", 1);
    typeCB.addItem("Polveri PM 2,5", 2);
    addFrame(QString::fromStdString("Tipo di Sensore: "), typeCB, *mainLayout);

    connect(&typeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(showType(int)));

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

    mainLayout->addWidget(&dataL);
    dataL.hide();

    
    dataOutFrame.setFrameShape(QFrame::StyledPanel);
    dataOutFrame.setFixedHeight(140);
    QHBoxLayout* dataOutFrameLayout = new QHBoxLayout(&dataOutFrame);
    mainLayout->addWidget(&dataOutFrame);
    dataOutFrame.hide();

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
    tableWidget->setItem(2, 1, xAxisTitleItem);
    

    // Set button with "+" text in row 0, column 2 rowspan 3 and columnspan 1
    tableWidget->setCellWidget(0, 2, addP);
    addP->setStyleSheet("background-color: green");
    connect(addP, SIGNAL(clicked()), this, SLOT(addPoint()));
    tableWidget->setSpan(0, 2, 3, 1);

    dataOutFrameLayout->addWidget(tableWidget);


    QFrame* save_disc_Frame = new QFrame(ScrollFrame);
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
    std::string name = titleLE.text().toStdString();
    std::string shortDescription = shortDescLE.text().toStdString();
    std::string longDescription = longDescTE.toPlainText().toStdString();
    std::string xAxisLabel = tableWidget->item(2,1)->text().toStdString();
     
    unsigned int simulationSpan = spanSimulLE.text().toUInt();
    float sensibility = sensibilityLE.text().toFloat();
    float maxMeasurable = maxLE.text().toFloat();
    float minMeasurable = minLE.text().toFloat();

    AbstractSensor* sensor= nullptr;
    
    int sw = typeCB.currentIndex();
    if(sw == 0){
        float r0 = tempR0.text().toFloat();
        float alpha = tempAlpha.text().toFloat();
        float beta = tempBeta.text().toFloat();
        float gamma = tempGamma.text().toFloat();
        float delta = tempDelta.text().toFloat();
        float epsilon = tempEpsilon.text().toFloat();
        float zeta = tempZeta.text().toFloat();

        sensor = new TemperaturePRTS(name,shortDescription,longDescription,xAxisLabel,simulationSpan,sensibility,maxMeasurable,minMeasurable,r0,alpha,beta,gamma,delta,epsilon,zeta);
    }else if (sw == 1){
        float Ah = humidA.text().toFloat();
        float Bh = humidB.text().toFloat();
        float Ch = humidC.text().toFloat();
        
        sensor = new HumidityNTCS(name,shortDescription,longDescription,xAxisLabel,simulationSpan,sensibility,maxMeasurable,minMeasurable,Ah,Bh,Ch);
    }else if(sw == 2){
        float Ad = dustA.text().toFloat();
        float Bd = dustB.text().toFloat();
            
        sensor = new Dust25S(name,shortDescription,longDescription,xAxisLabel,simulationSpan,sensibility,maxMeasurable,minMeasurable,Ad,Bd);
    }else {
         std::cerr << "Unexpected sensor type selected in SensorDialog::save()";
    }
    
    for (int column = 2; column < tableWidget->columnCount()-1; column++) {
        QTableWidgetItem* yItem = tableWidget->item(1, column);
        QTableWidgetItem* xItem = tableWidget->item(2, column);
        if (yItem && xItem) {
            float y = yItem->text().toFloat();
            float x = xItem->text().toFloat();
            std::array<float, 2> p = {y, x};
            sensor->addPoint(p);
        }
    }
    manager.addSensor(sensor);
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
    addP->setIndex(columnCount);
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
    addP->setIndex(tableWidget->columnCount());
}



}
}
