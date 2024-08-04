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
MainSensorView::MainSensorView(AbstractSensor *sensor , QWidget *parent)
: QWidget(parent), sensor(sensor)
{

    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(MainSensorViewLayout);
    
    QFrame* titleFrame = new QFrame(this);
    QHBoxLayout* titleFrameLayout = new QHBoxLayout(titleFrame);
    titleFrame->setLayout(titleFrameLayout);

    title = new QLabel(QString::fromStdString(sensor->getName()), titleFrame);
    titleFrameLayout->addWidget(title);
    titleFrameLayout->addStretch();

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
MainSensorView::MainSensorView(QWidget* parent): QWidget(parent), sensor(nullptr)
{
    QVBoxLayout* MainSensorViewLayout = new QVBoxLayout(this);
    MainSensorViewLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(MainSensorViewLayout);
    
    QFrame* titleFrame = new QFrame(this);
    QHBoxLayout* titleFrameLayout = new QHBoxLayout(titleFrame);
    titleFrame->setLayout(titleFrameLayout);

    title = new QLabel(QString::fromStdString("Titolo Sensore"), titleFrame);
    
    titleFrameLayout->addWidget(title);
    titleFrameLayout->addStretch();

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

void MainSensorView::update( AbstractSensor* s){
    if(sensor == nullptr){
        title->setText("Titolo sensore:");
        type->setText("Sensore:");
        sensibility->setText("Sensibilità:");
        min->setText("Min:");
        max->setText("Max:");
        mean->setText("Media:");
        variance->setText("Varianza:");
        longDesc->setText("Descrizione Lunga:");
        series->clear();
        chartView->show();
        chart->setTitle("Titolo Sensore:");
        QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
        for (QAbstractAxis* axis : horizontalAxes) {
            axis->setTitleText(QString::fromStdString("x"));
            
        }
        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        for (QAbstractAxis* axis : verticalAxes) {
            axis->setTitleText(QString::fromStdString("y"));
        }
        return;
    }
    else{
        title->setText(QString::fromStdString(sensor->getName()));
        type->setText(QString::fromStdString("Sensore: " + sensor->getSensorType()));
        sensibility->setText(QString::fromStdString("Sensibilità: " + std::to_string(sensor->getSensibility())));
        min->setText(QString::fromStdString("Min: " + std::to_string(sensor->getMin())));
        max->setText(QString::fromStdString("Max: " + std::to_string(sensor->getMax())));
        mean->setText(QString::fromStdString("Media: " + std::to_string(sensor->getAverage())));
        variance->setText(QString::fromStdString("Varianza: " +std::to_string(sensor->getVariance())));
        longDesc->setText(QString::fromStdString(sensor->getLongDescription()));

        chart->removeAllSeries();
        series = new QLineSeries();
        double upperY, lowerY, upperX, lowerX;
        if(sensor->getMeasure().size() != 0){
            upperY =  sensor->getMeasure()[0][0];
            lowerY = sensor->getMeasure()[0][0];
            upperX = sensor->getMeasure()[0][1];
            lowerX = sensor->getMeasure()[0][1];
        }
        
        for (auto point : sensor->getMeasure()) {
            if(point[0] > upperY) upperY = point[0];
            if(point[0] < lowerY) lowerY = point[0];
            if(point[1] > upperX) upperX = point[1];
            if(point[1] < lowerX) lowerX = point[1];
            series->append(point[1], point[0]); 
        }

        chart->addSeries(series);
        QList<QAbstractAxis *> horizontalAxes = chart->axes(Qt::Horizontal);
        for (QAbstractAxis* axis : horizontalAxes) {
            axis->setTitleText(QString::fromStdString(sensor->getXAxisLabel()));
            axis->setRange(lowerX, upperX);
        }
        QList<QAbstractAxis *> verticalAxes = chart->axes(Qt::Vertical);
        for (QAbstractAxis* axis : verticalAxes) {
            axis->setTitleText(QString::fromStdString(sensor->getYAxisLabel()));
            axis->setRange(lowerY, upperY);
        }
        chart->setTitle(QString::fromStdString(sensor->getName()));
        chartView->setMinimumSize(this->width()-100, this->width()/2);
    }
};



void  MainSensorView::changeSensor(AbstractSensor* sensorPointer){
    if (sensor){
        sensor->removeObserver(this);
    }
    if(sensorPointer){
        sensorPointer->addObserver(this);
    }
    sensor = sensorPointer;
    update();
};
    


}
}
