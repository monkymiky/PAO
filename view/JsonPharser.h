#ifndef JSONPHARSER_H
#define JSONPHARSER_H


#include "../sensor/SensorManager.h"
#include "../view/Aside.h"
#include "JsonVisitor.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"
#include "../sensor/TemperatureS.h"
#include "../sensor/HumidityS.h"
#include "../sensor/Dust25S.h"
#include <iostream>

namespace Sensor{

    class JsonPharser{
    public:
        static void savetoJson(const SensorManager& manager, const QString& filename);

        static void openfromJson(SensorManager& manager, View::Aside& aside,  View::MainWindow* mainWindow, const QString& filename);
    };

}
#endif
