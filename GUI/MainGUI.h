

#ifndef CARWASH_MAINGUI_H
#define CARWASH_MAINGUI_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <vector>
#include "../Domain/car.h"

class MainGUI : public QWidget {
public:
    explicit MainGUI(Service& serv) : serv{ serv } {
        initGUI();
        loadData(serv.get_all_cars_srv());
        initConnect();
    }

private:
    Service& serv;
    QTableView* tableCars = new QTableView;
    QPushButton* btnSortRegistration = new QPushButton{"&Registration" };
    QPushButton* btnSortByProducerModel= new QPushButton{"&Producer and Model" };
    QPushButton* btnSortByType = new QPushButton{"&Type" };

    QLineEdit* lineCRUDRegistration = new QLineEdit;
    QLineEdit* lineCRUDProducer = new QLineEdit;
    QLineEdit* lineCRUDModel = new QLineEdit;
    QComboBox* chooseType = new QComboBox;

    QPushButton* btnAdd = new QPushButton{ "&Add" };
    QPushButton* btnDelete = new QPushButton{"&Delete" };
    QPushButton* btnModify = new QPushButton{"&Modify" };
    QPushButton* btnUndo = new QPushButton{ "&Undo" };

    QLineEdit* lineSearchRegistration = new QLineEdit;
    QLineEdit* lineSearchProducer = new QLineEdit;
    QLineEdit* lineSearchModel = new QLineEdit;
    QLineEdit* lineSearchType = new QLineEdit;

    QPushButton* btnCarWash = new QPushButton{"&Car Wash" };
    QPushButton* btnTypeRaport = new QPushButton{"&Cars type raport" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };


    void initGUI();
    void loadData(const vector<Car>& cars);
    void initConnect();
    void onCarSelected();

    QVBoxLayout *getCarsListLayout();
    static QFrame *getVLine();
    QVBoxLayout *getCRUDOperaitionsLayout();
    QFormLayout *getAddModifyDeleteForm();
    QHBoxLayout *getAddModifyDeleteMenu();
    static QFrame *getHLine();
    QFormLayout *getSearchForm();
    QHBoxLayout *getLastMenu();

    void connectSelectionModel();
    void connectSearchFields();
    void connectButtons();

    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onModifyButtonClicked();
    void onUndoButtonClicked();
    void onCarWashButtonClicked();
    void onRaportButtonClicked();
    void onSortRegistrationButtonClicked();
    void onSortByProducerModelButtonClicked();
    void onSortByTypeButtonClicked();
};

#endif //CARWASH_MAINGUI_H
