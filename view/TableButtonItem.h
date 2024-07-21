#ifndef TABLEBUTTONITEM_H
#define TABLEBUTTONITEM_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidgetItem>

namespace Sensor {
namespace View {
class TableButtonItem : public QPushButton, public QTableWidgetItem {
    Q_OBJECT
    private:
        int index;
    public:
        TableButtonItem(const QString& text,int index, QWidget* parent = nullptr): QPushButton(text, parent), QTableWidgetItem(text), index(index){};
        int getIndex() const {return index;};
        void setIndex(int index){this->index = index;};  
};
}
}

#endif