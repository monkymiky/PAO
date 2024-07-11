#include "SensorDialog.h"
#include <math.h>
#include "../sensor/Dust25S.h"
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h"

#include <iostream>

namespace Sensor {
namespace View {
void SensorDialog::addFrame(QString label, QWidget & widget, QLayout& layout){
    QFrame *Frame = new QFrame();
    Frame->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout *frameLayout = new QHBoxLayout(Frame);
    QLabel *Lab = new QLabel(label);
    frameLayout->addWidget(Lab);
    frameLayout->addWidget(&widget);

    layout.addWidget(Frame);
};
void SensorDialog::addPoint(){
    QLineEdit * x = new QLineEdit(this);
    QLineEdit * y = new QLineEdit(this);
    std::array<QLineEdit*,2> array = {x,y};
    points.push_back(array);

    auto col = dataLayout->columnCount();
    dataLayout->removeWidget(&addP);

    QPushButton* rmPoint = new QPushButton("x", this);
    dataLayout->addWidget(rmPoint,0,col);
    dataLayout->addWidget(y,0,col);
    dataLayout->addWidget(x,0,col);
    dataLayout->addWidget(&addP,1,col+1,1,2);

}

void SensorDialog::showType(int index){
    tempFrame.hide();
    humidFrame.hide();
    dustFrame.hide();
    switch(index){
        case 0:
            tempFrame.show();
            break;
        case 1:
            humidFrame.show();
            break;
        case 2:
            dustFrame.show();
            break;
        default:
            std::cerr << "Unexpected sensor type selected in SensorDialog::showType()";
    }
}
SensorDialog::~SensorDialog(){
    for(auto point : points){
        delete point[0];
        delete point[1];
    }
    close();
    deleteLater();
}
SensorDialog::SensorDialog(SensorManager* manager, QWidget* parent): 
manager(manager),
titleLE( QLineEdit(this)),
shortDescLE( QLineEdit(this)),
longDescTE( QTextEdit(this)),
sensibilityLE( QLineEdit(this)),
spanSimulLE( QLineEdit(this)),
typeCB( QComboBox(this)),
xAxisLE( QLineEdit(this)),
maxLE( QLineEdit(this)),
minLE( QLineEdit(this)),
dustA( QLineEdit(this)),
dustB( QLineEdit(this)),
humidA( QLineEdit(this)),
humidB( QLineEdit(this)),
humidC( QLineEdit(this)),
tempR0( QLineEdit(this)),
tempAlpha( QLineEdit(this)),
tempBeta( QLineEdit(this)),
tempGamma( QLineEdit(this)),
tempDelta( QLineEdit(this)),
tempEpsilon( QLineEdit(this)),
tempZeta( QLineEdit(this)),
tempFrame( QFrame(this)),
humidFrame( QFrame(this)),
dustFrame( QFrame(this)),
points(std::vector<std::array<QLineEdit*, 2>>()),
addP( QPushButton("+")),
QDialog(parent)
{

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QScrollArea* ScrollArea = new QScrollArea(this);
    mainLayout->addWidget(ScrollArea);
    QVBoxLayout* scrollLayout = new QVBoxLayout(ScrollArea);

    addFrame(QString::fromStdString("Titolo: "), titleLE, *scrollLayout);
    addFrame(QString::fromStdString("Descrizione corta: "), shortDescLE, *scrollLayout);
    addFrame(QString::fromStdString("Descrizione Lunga: "), longDescTE, *scrollLayout);
    addFrame(QString::fromStdString("Sensibilità: "), sensibilityLE, *scrollLayout);
    addFrame(QString::fromStdString("Massimo misurabile: "), maxLE, *scrollLayout);
    addFrame(QString::fromStdString("Minimo misurabile: "), minLE, *scrollLayout);
    addFrame(QString::fromStdString("Intervallo simulazione: "), spanSimulLE, *scrollLayout);

    typeCB.addItem("Temperatura NTP", 0);
    typeCB.addItem("Umidità NTC",1);
    typeCB.addItem("Polveri PM 2,5", 2);
    addFrame(QString::fromStdString("Tipo di Sensore: "), typeCB, *scrollLayout);

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

    scrollLayout->addWidget(&tempFrame);
    tempFrame.hide();

    humidFrame.setFrameShape(QFrame::StyledPanel);
    QGridLayout* humidLayout = new QGridLayout(&humidFrame);
    addFrame(QString::fromStdString("A : "), humidA, *humidLayout);
    addFrame(QString::fromStdString("B : "), humidB, *humidLayout);
    addFrame(QString::fromStdString("C : "), humidC, *humidLayout);

    scrollLayout->addWidget(&humidFrame);
    humidFrame.hide();

    dustFrame.setFrameShape(QFrame::StyledPanel);
    QGridLayout* dustLayout = new QGridLayout(&dustFrame);
    addFrame(QString::fromStdString("A : "), dustA, *dustLayout);
    addFrame(QString::fromStdString("B : "), dustB, *dustLayout);

    scrollLayout->addWidget(&dustFrame);
    dustFrame.hide();

    QLabel* dataL  = new QLabel("Misurazioni: ");
    scrollLayout->addWidget(dataL);
    dataL->hide();

    QFrame* dataOutFrame = new QFrame(this);
    dataOutFrame->setFrameShape(QFrame::StyledPanel);
    QHBoxLayout* dataOutFrameLayout = new QHBoxLayout(dataOutFrame);
    dataOutFrame->hide();

    QFrame* headers = new QFrame(dataOutFrame);
    QGridLayout* headersLayout = new QGridLayout(headers);
    QLabel* emptyLabel = new QLabel("");
    QLabel* yAxis = new QLabel("Asse Y");
    QLabel* yAxisTitle = new QLabel("Asse Y");
    QLabel* xAxis = new QLabel("Asse X"); 

    headersLayout->addWidget(emptyLabel,0,0);
    headersLayout->addWidget(emptyLabel,1,0);
    headersLayout->addWidget(yAxis,0,1);
    headersLayout->addWidget(yAxisTitle,1,1);
    headersLayout->addWidget(xAxis,2,0);
    headersLayout->addWidget(&xAxisLE,2,1);

    dataOutFrameLayout->addWidget(headers);

    QFrame* dataFrame = new QFrame(dataOutFrame);
    dataLayout = new QGridLayout(dataFrame);
    
    dataLayout->addWidget(emptyLabel, 0,0);
    dataLayout->addWidget(&addP, 0,1,1,2);



    QPushButton * discard = new QPushButton("Annulla", this);
    scrollLayout->addWidget(discard);
    scrollLayout->addStretch();
    QPushButton * save = new QPushButton("Salva", this);
    scrollLayout->addWidget(save);
    
    connect(discard, SIGNAL(clicked()), this,SLOT(close()));
    connect(save, SIGNAL(clicked()), this,SLOT(saveSensor()));
    this->resize(1000,1000);
    QString styleSheet = "QLineEdit { height: 30px; }";
    this->setStyleSheet(styleSheet);
};
void SensorDialog::saveSensor(){
    std::string name = titleLE.text().toStdString();
    std::string shortDescription = shortDescLE.text().toStdString();
    std::string longDescription = longDescTE.toPlainText().toStdString();
    std::string xAxisLabel = xAxisLE.text().toStdString();
     
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
    
    for(auto point :points){
        float y = point[0]->text().toFloat();
        float x = point[1]->text().toFloat();
        std::array<float,2> p = {y,x};
        sensor->addPoint(p);
    }
    manager->addSensor(sensor);
    closeDialog();
};
void SensorDialog::closeDialog(){
    accept();
    close();
    deleteLater();
};

}
}
