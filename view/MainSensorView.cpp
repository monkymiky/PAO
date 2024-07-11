#include "MainSensorView.h"
#include <vector>
#include <array>
#include <iostream> 
#include <QtCharts/QXYSeries>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "SensorDialog.h"
#include <QtCharts/QChartView>

namespace Sensor { 
namespace View {
MainSensorView::MainSensorView(QWidget* parent): QWidget(parent), sensor(nullptr){
    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QFrame* titleFrame = new QFrame();
    QHBoxLayout* titleFrameLayout = new QHBoxLayout(titleFrame);
    titleFrame->setLayout(titleFrameLayout);

    title = new QLabel(QString::fromStdString("Nome Sensore"), titleFrame);
    QPushButton *buttonSimulate = new QPushButton("Simula", titleFrame);
    QPushButton *buttonModify = new QPushButton("Modifica", titleFrame);
    QPushButton *buttonDelete = new QPushButton("Elimina", titleFrame);
    titleFrameLayout->addWidget(title);
    titleFrameLayout->addStretch();
    titleFrameLayout->addWidget(buttonSimulate);
    titleFrameLayout->addWidget(buttonModify);
    titleFrameLayout->addWidget(buttonDelete);

    connect(buttonModify, SIGNAL(clicked()), this,SLOT(openSensorDialog()));
    connect(buttonDelete, SIGNAL(clicked()), this,SLOT(deleteSensor()));
    connect(buttonSimulate, SIGNAL(clicked()), this,SLOT(simulate()));

    MainSensorViewLayout->addWidget(titleFrame);

    QFrame* infoFrame = new QFrame();
    QGridLayout* infoFrameLayout = new QGridLayout(infoFrame);
    infoFrame->setLayout(infoFrameLayout);

    type = new QLabel("Sensore: " , infoFrame);
    sensibility = new QLabel("Sensibilità: ", infoFrame);
    min = new QLabel("Min: " , infoFrame);
    max = new QLabel("Max: " , infoFrame);
    mean = new QLabel("Media: " , infoFrame);
    variance = new QLabel("Varianza: ", infoFrame);
    
    infoFrameLayout->addWidget(type);
    infoFrameLayout->addWidget(sensibility);
    infoFrameLayout->addWidget(min);
    infoFrameLayout->addWidget(max);
    infoFrameLayout->addWidget(mean);
    infoFrameLayout->addWidget(variance);

    QScrollArea *ScrollArea = new QScrollArea(this);
    QHBoxLayout* ScrollAreaLayout = new QHBoxLayout(ScrollArea);
    // Chart creation
    series = new QLineSeries();
    chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
    for (QAbstractAxis* axis : horizontalAxes) {
        axis->setTitleText(QString::fromStdString("x"));
    }
    QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
    for (QAbstractAxis* axis : verticalAxes) {
        axis->setTitleText(QString::fromStdString("y"));
    }
    chart->setTitle(QString::fromStdString("titolo"));
    chartView = new QChartView(chart);
    ScrollAreaLayout->addWidget(chartView);

    longDesc = new QLabel(QString::fromStdString(""), ScrollArea);
    longDesc->setWordWrap(true);

    MainSensorViewLayout->addWidget(ScrollArea);
};
 MainSensorView::MainSensorView(AbstractSensor* sensor, QWidget* parent)
 : QWidget(parent), sensor(sensor){
    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    QFrame* titleFrame = new QFrame();
    QHBoxLayout* titleFrameLayout = new QHBoxLayout(titleFrame);
    titleFrame->setLayout(titleFrameLayout);

    title = new QLabel(QString::fromStdString(sensor->getName()), titleFrame);
    QPushButton *buttonSimulate = new QPushButton("Simula", titleFrame);
    QPushButton *buttonModify = new QPushButton("Modifica", titleFrame);
    QPushButton *buttonDelete = new QPushButton("Elimina", titleFrame);
    titleFrameLayout->addWidget(title);
    titleFrameLayout->addStretch();
    titleFrameLayout->addWidget(buttonSimulate);
    titleFrameLayout->addWidget(buttonModify);
    titleFrameLayout->addWidget(buttonDelete);

    connect(buttonModify, SIGNAL(clicked()), this,SLOT(openSensorDialog()));
    connect(buttonDelete, SIGNAL(clicked()), this,SLOT(deleteSensor()));
    connect(buttonSimulate, SIGNAL(clicked()), this,SLOT(simulate()));

    MainSensorViewLayout->addWidget(titleFrame);

    QFrame* infoFrame = new QFrame();
    QGridLayout* infoFrameLayout = new QGridLayout(infoFrame);
    infoFrame->setLayout(infoFrameLayout);

    type = new QLabel("Sensore: " + QString::fromStdString(sensor->getSensorType()), infoFrame);
    sensibility = new QLabel("Sensibilità: " + QString::number(sensor->getSensibility()), infoFrame);
    min = new QLabel("Min: " + QString::number(sensor->getMin()), infoFrame);
    max = new QLabel("Max" + QString::number(sensor->getMax()), infoFrame);
    mean = new QLabel("Media" + QString::number(sensor->getAverage()), infoFrame);
    variance = new QLabel("Varianza" + QString::number(sensor->getVariance()), infoFrame);
    
    infoFrameLayout->addWidget(type);
    infoFrameLayout->addWidget(sensibility);
    infoFrameLayout->addWidget(min);
    infoFrameLayout->addWidget(max);
    infoFrameLayout->addWidget(mean);
    infoFrameLayout->addWidget(variance);

    QScrollArea *ScrollArea = new QScrollArea(this);
    QHBoxLayout* ScrollAreaLayout = new QHBoxLayout(ScrollArea);
    // Chart creation
    series = new QLineSeries();
    for (auto point : sensor->getMeasure()) {
        series->append(point[1], point[0]); 
    }
    chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
    for (QAbstractAxis* axis : horizontalAxes) {
        axis->setTitleText(QString::fromStdString(sensor->getXAxisLabel()));
    }
    QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
    for (QAbstractAxis* axis : verticalAxes) {
        axis->setTitleText(QString::fromStdString(sensor->getYAxisLabel()));
    }
    chart->setTitle(QString::fromStdString(sensor->getName()));
    chartView = new QChartView(chart);
    ScrollAreaLayout->addWidget(chartView);

    longDesc = new QLabel(QString::fromStdString(sensor->getName()), ScrollArea);
    longDesc->setWordWrap(true);

    MainSensorViewLayout->addWidget(ScrollArea);
    
};

void MainSensorView::update(AbstractSensor* sensor) {
    if(sensor == nullptr){
        std::cerr << "sensor is null MainSensorView::update" << std::endl;
        return;
    }
    title->setText(QString::fromStdString(sensor->getName()));
    type->setText(QString::fromStdString(sensor->getSensorType()));
    sensibility->setText(QString::number(sensor->getSensibility()));
    min->setText(QString::number(sensor->getMin()));
    max->setText(QString::number(sensor->getMax()));
    mean->setText(QString::number(sensor->getAverage()));
    variance->setText(QString::number(sensor->getVariance()));
    longDesc->setText(QString::fromStdString(sensor->getLongDescription()));

    for (auto point : sensor->getMeasure()) {
        series->append(point[1], point[0]); 
    }
    chart->removeAllSeries();
    chart->addSeries(series);
    QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
    for (QAbstractAxis* axis : horizontalAxes) {
        axis->setTitleText(QString::fromStdString(sensor->getXAxisLabel()));
    }
    QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
    for (QAbstractAxis* axis : verticalAxes) {
        axis->setTitleText(QString::fromStdString(sensor->getYAxisLabel()));
    }
    chart->setTitle(QString::fromStdString(sensor->getName()));
};

void  MainSensorView::changeSensor(AbstractSensor* sensorPointer){
    sensor = sensorPointer;
    update(sensor);
};

void  MainSensorView::openSensorDialog(){
    //SensorDialog dialog =  SensorDialog(sensorManager);
    //dialog.exec();
};

void MainSensorView::deleteSensor(){
    delete(sensor);
    title->setText("deleted sensor");
    type->setText("");
    sensibility->setText("");
    min->setText("");
    max->setText("");
    mean->setText("");
    variance->setText("");
    longDesc->setText("deleted sensor");
    delete(chart);
};

void MainSensorView::simulate(){
    sensor->simulate();
};
}
}
