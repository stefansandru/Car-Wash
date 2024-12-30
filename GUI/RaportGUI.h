

#ifndef CARWASH_RAPORTGUI_H
#define CARWASH_RAPORTGUI_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <map>
#include <string>
#include "../Service/service.h"
#include "../Domain/CarTypeCountDTO.h"

class RaportGUI : public QWidget {
private:
    Service &service;
    QTableView* tableTypeAndCarsCount = new QTableView;
    QPushButton* btnExit = new QPushButton{ "&Exit" };

public:
    explicit RaportGUI(Service& service) : service{ service } {
        initGUI();
        loadTable(service.typeAndNumberOfCars());
        initConnect();
    }

    void initGUI();
    void loadTable(const map<string, CarTypeCountDTO>& typeAndCarsCount);
    void initConnect();
};


#endif //CARWASH_RAPORTGUI_H
