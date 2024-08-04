#ifndef JSONPHARSER_H
#define JSONPHARSER_H


#include "SensorManager.h"
#include "../view/Aside.h"
#include "JsonVisitor.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"
#include "TemperatureS.h"
#include "HumidityS.h"
#include "Dust25S.h"
#include <iostream>

namespace Sensor{

    class JsonPharser{
    public:
        static void savetoJson(const SensorManager& manager, const QString& filename);

        static void openfromJson(SensorManager& manager, View::Aside& aside,View::MainWindow* mainWindow, const QString& filename);
    };

}
#endif