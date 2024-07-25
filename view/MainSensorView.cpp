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
MainSensorView::MainSensorView(AbstractSensor *sensor,SensorManager& manager , QWidget *parent)
: QWidget(parent),manager(manager) , sensor(sensor)
{

    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(MainSensorViewLayout);
    
    QFrame* titleFrame = new QFrame(this);
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

    
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

    MainSensorViewLayout->addWidget(scrollArea);

    QFrame* ScrollFrame = new QFrame(this);
    QGridLayout* ScrollFrameLayout = new QGridLayout(ScrollFrame);
    ScrollFrame->setLayout(ScrollFrameLayout);
    scrollArea->setWidget(ScrollFrame);

    QFrame* infoFrame = new QFrame(this);
    QGridLayout* infoFrameLayout = new QGridLayout(infoFrame);
    infoFrame->setLayout(infoFrameLayout);

    type = new QLabel("Sensore: " + QString::fromStdString(sensor->getSensorType()), infoFrame);
    sensibility = new QLabel("Sensibilità: " + QString::number(sensor->getSensibility()), infoFrame);
    min = new QLabel("Min: " + QString::number(sensor->getMin()), infoFrame);
    max = new QLabel("Max: " + QString::number(sensor->getMax()), infoFrame);
    mean = new QLabel("Media: " + QString::number(sensor->getAverage()), infoFrame);
    variance = new QLabel("Varianza: " + QString::number(sensor->getVariance()), infoFrame);
    
    infoFrameLayout->addWidget(type, 0, 0);
    infoFrameLayout->addWidget(sensibility, 1, 0);
    infoFrameLayout->addWidget(min, 0, 1);
    infoFrameLayout->addWidget(max, 1, 1);
    infoFrameLayout->addWidget(mean, 0, 2);
    infoFrameLayout->addWidget(variance, 1, 2);

    ScrollFrameLayout->addWidget(infoFrame);

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

    chartView->setMinimumSize(scrollArea->width(), scrollArea->width());

    ScrollFrameLayout->addWidget(chartView);

    longDesc = new QLabel(QString::fromStdString(sensor->getLongDescription()), ScrollFrame);
    
    longDesc->setWordWrap(true);
    ScrollFrameLayout->addWidget(longDesc);

    
}
MainSensorView::~MainSensorView() {
    delete(chart);
    delete(chartView);
    delete(series);
};
MainSensorView::MainSensorView(SensorManager& manager,  QWidget* parent): manager(manager), QWidget(parent), sensor(nullptr)
{
    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(MainSensorViewLayout);
    
    QFrame* titleFrame = new QFrame(this);
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

    
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

    MainSensorViewLayout->addWidget(scrollArea);

    QFrame* ScrollFrame = new QFrame(this);
    QGridLayout* ScrollFrameLayout = new QGridLayout(ScrollFrame);
    ScrollFrame->setLayout(ScrollFrameLayout);
    scrollArea->setWidget(ScrollFrame);

    QFrame* infoFrame = new QFrame(this);
    QGridLayout* infoFrameLayout = new QGridLayout(infoFrame);
    infoFrame->setLayout(infoFrameLayout);

    type = new QLabel("Sensore: " , infoFrame);
    sensibility = new QLabel("Sensibilità: ", infoFrame);
    min = new QLabel("Min: " , infoFrame);
    max = new QLabel("Max: " , infoFrame);
    mean = new QLabel("Media: " , infoFrame);
    variance = new QLabel("Varianza: ", infoFrame);

    infoFrameLayout->addWidget(type, 0, 0);
    infoFrameLayout->addWidget(sensibility, 1, 0);
    infoFrameLayout->addWidget(min, 0, 1);
    infoFrameLayout->addWidget(max, 1, 1);
    infoFrameLayout->addWidget(mean, 0, 2);
    infoFrameLayout->addWidget(variance, 1, 2);

    ScrollFrameLayout->addWidget(infoFrame);

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
    ScrollFrameLayout->addWidget(chartView);
   
    chartView->setMinimumSize(scrollArea->width(), scrollArea->width());

    longDesc = new QLabel(QString::fromStdString(""), ScrollFrame);
    
    longDesc->setWordWrap(true);
    ScrollFrameLayout->addWidget(longDesc);
    
};

void MainSensorView::update(AbstractSensor* newsensor) {
    if(sensor != nullptr){
        sensor->removeObserver(this);
    }
     
    std::cout << "update main" << std::endl;
    if(newsensor == nullptr){
        std::cerr << "sensor is null MainSensorView::update" << std::endl;
        return;
    }

    title->setText(QString::fromStdString(newsensor->getName()));
    type->setText(QString::fromStdString("Sensore: " + newsensor->getSensorType()));
    sensibility->setText(QString::fromStdString("Sensibilità: " + std::to_string(newsensor->getSensibility())));
    min->setText(QString::fromStdString("Min: " + std::to_string(newsensor->getMin())));
    max->setText(QString::fromStdString("Max: " + std::to_string(newsensor->getMax())));
    mean->setText(QString::fromStdString("Media: " + std::to_string(newsensor->getAverage())));
    variance->setText(QString::fromStdString("Varianza: " +std::to_string(newsensor->getVariance())));
    longDesc->setText(QString::fromStdString(newsensor->getLongDescription()));

    chart->removeAllSeries();
    series = new QLineSeries();
    for (auto point : newsensor->getMeasure()) {
        series->append(point[1], point[0]); 
    }
    chart->addSeries(series);
    QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
    for (QAbstractAxis* axis : horizontalAxes) {
        axis->setTitleText(QString::fromStdString(newsensor->getXAxisLabel()));
    }
    QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
    for (QAbstractAxis* axis : verticalAxes) {
        axis->setTitleText(QString::fromStdString(newsensor->getYAxisLabel()));
    }
    chart->setTitle(QString::fromStdString(newsensor->getName()));
    chartView->setMinimumSize(this->width()-50, this->width()-50);
    sensor = newsensor;
    sensor->addObserver(this);
};

void  MainSensorView::changeSensor(AbstractSensor* sensorPointer){
    sensor = sensorPointer;
    update(sensor);
};

void  MainSensorView::openSensorDialog(){
    SensorDialog* typeDialog = new SensorDialog( manager, sensor, qobject_cast<QWidget*>(parent()));
    typeDialog->exec();
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
    delete(chartView);
    delete(series);
};

void MainSensorView::simulate(){
    sensor->simulate();
};
}
}
