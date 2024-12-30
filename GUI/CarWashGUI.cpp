
#include "CarWashGUI.h"
#include "../Export/export.h"
#include "../Exceptions//ExportException.h"
#include "CarsTableModel.h"
#include "../Exceptions/RepoException.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>


void CarWashGUI::initGUI() {
    tableCars->setMinimumSize(520, 300);

    auto* mainLayout = new QHBoxLayout;
    setLayout(mainLayout);
    mainLayout->addLayout(getWaitingListLayout());
    mainLayout->addLayout(getOperationsLayout());
}

QVBoxLayout *CarWashGUI::getOperationsLayout() {
    auto* OperationsLayout = new QVBoxLayout;
    OperationsLayout->addLayout(getAddCarLayout());
    OperationsLayout->addLayout(getRandomAddLayout());
    OperationsLayout->addWidget(btnClearCarWash);
    OperationsLayout->addWidget(getHLine());
    OperationsLayout->addLayout(getExportAndExitLayout());
    return OperationsLayout;
}

QVBoxLayout *CarWashGUI::getWaitingListLayout() {
    auto* waitingListLayout = new QVBoxLayout;
    auto* titluLista = new QLabel;
    titluLista->setText("Waiting list");

    waitingListLayout->addWidget(titluLista);
    waitingListLayout->addWidget(tableCars);
    return waitingListLayout;
}

QHBoxLayout *CarWashGUI::getExportAndExitLayout() {
    auto exportLayout = new QHBoxLayout;
    exportLayout->addWidget(btnToCsv);
    exportLayout->addWidget(btnToHtml);
    exportLayout->addWidget(btnExit);
    btnExit->setStyleSheet("background-color: #b30000;"
                           " color: white; border: 1px solid black; "
                           "border-radius: 5px;"
                           " height: 17px;");
    return exportLayout;
}

QFrame *CarWashGUI::getHLine() {
    auto* HLine1 = new QFrame();
    HLine1->setFrameShape(QFrame::HLine);
    HLine1->setLineWidth(1 / 4);
    HLine1->setStyleSheet("color: gray;");
    return HLine1;
}

QHBoxLayout *CarWashGUI::getRandomAddLayout() {
    auto* randomAddLayout = new QHBoxLayout;
    auto randomAddForm = new QFormLayout;
    randomAddForm->addRow("How many random cars?", txtNrOfCars);
    randomAddLayout->addLayout(randomAddForm);
    randomAddLayout->addWidget(btnAddRandon);
    return randomAddLayout;
}

QHBoxLayout *CarWashGUI::getAddCarLayout() {
    auto* addCarLayout = new QHBoxLayout;
    auto* addForm = new QFormLayout;
    addForm->addRow("Registration", txtRegistration);
    addCarLayout->addLayout(addForm);
    addCarLayout->addWidget(btnAddCarWash);
    return addCarLayout;
}

void CarWashGUI::loadTable(const vector<Car>& carsList) {
    auto* model = new CarsTableModel(carsList, this);
    tableCars->setModel(model);
}

void CarWashGUI::initConnect() {
    connectAddCarWashButton();
    connectClearCarWashButton();
    connectAddRandomButton();
    connectExitButton();
    connectExportButtons();
}

void CarWashGUI::connectAddCarWashButton() {
    QObject::connect(btnAddCarWash, &QPushButton::clicked, [&]() {
        try {
            auto registration = txtRegistration->text().toStdString();
            service.addToWaitingList_srv(registration);
            loadTable(service.getWaitingList());
        } catch (ExportException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        } catch (RepoException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
}

void CarWashGUI::connectClearCarWashButton() {
    QObject::connect(btnClearCarWash, &QPushButton::clicked, [&]() {
        try {
            service.clearWaitingList_srv();
            loadTable(service.getWaitingList());
        } catch (ExportException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
}

void CarWashGUI::connectAddRandomButton() {
    QObject::connect(btnAddRandon, &QPushButton::clicked, [&]() {
        try {
            int nr_of_cars = txtNrOfCars->text().toInt();
            service.randomAddToWaitingList_srv(nr_of_cars);
            loadTable(service.getWaitingList());
        } catch (ExportException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
}

void CarWashGUI::connectExitButton() {
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        close();
    });
}

void CarWashGUI::connectExportButtons() {
    QObject::connect(btnToCsv, &QPushButton::clicked, [&]() {
        try {
            exportToCVS("../DataStorage/carWash.csv",
                        service.getWaitingList());
            QMessageBox::information(this, "Information", "Exported to CSV.\nCheck carWash.csv file in DataStorage folder.");
        } catch (const ExportException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });

    QObject::connect(btnToHtml, &QPushButton::clicked, [&]() {
        try {
            exportToHTML("../DataStorage/carWash.html",
                         service.getWaitingList());
            QMessageBox::information(this, "Information", "Exported to HTML.\nCheck carWash.html file in DataStorage folder.");
        } catch (const ExportException &e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
}
