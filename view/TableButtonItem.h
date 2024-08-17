#ifndef TABLEBUTTONITEM_H
#define TABLEBUTTONITEM_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidgetItem>

namespace Sensor {
namespace View {
class TableButtonItem : public QPushButton, public QTableWidgetItem {
    Q_OBJECT
    private:
        int positionIndex;
    public:
        TableButtonItem(const QString& text,int positionIndex, QWidget* parent = nullptr)
        : QPushButton(text, parent), QTableWidgetItem(text), positionIndex(positionIndex){};
        int getpositionIndex() const;
        void setpositionIndex(int index);  
};
}
}

#endif