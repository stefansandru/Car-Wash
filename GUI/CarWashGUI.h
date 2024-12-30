

#ifndef CARWASH_CARWASHGUI_H
#define CARWASH_CARWASHGUI_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QHBoxLayout>
#include "../Service/service.h"
#include "../Domain/car.h"

class CarWashGUI : public QWidget {
private:
    Service& service;
    QTableView* tableCars = new QTableView;
    QLineEdit* txtRegistration = new QLineEdit;
    QLineEdit* txtNrOfCars = new QLineEdit;
    QPushButton* btnAddCarWash = new QPushButton{ "&Add to waiting list" };
    QPushButton* btnClearCarWash = new QPushButton{ "&Clear waiting list" };
    QPushButton* btnAddRandon = new QPushButton{ "&Add random cars" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnToCsv = new QPushButton{ "&Export to CSV" };
    QPushButton* btnToHtml = new QPushButton{ "&Export to Html" };

public:

    explicit CarWashGUI(Service& serv) : service{serv } {
        initGUI();
        initConnect();
        loadTable(serv.getWaitingList());
    }

    void initGUI();
    void loadTable(const vector<Car>& carsList);
    void initConnect();

    QHBoxLayout *getAddCarLayout();
    QHBoxLayout *getRandomAddLayout();
    QFrame *getHLine();
    QHBoxLayout *getExportAndExitLayout();
    QVBoxLayout *getWaitingListLayout();
    QVBoxLayout *getOperationsLayout();

    void connectAddCarWashButton();
    void connectClearCarWashButton();
    void connectAddRandomButton();
    void connectExitButton();
    void connectExportButtons();
};

#endif //CARWASH_CARWASHGUI_H
