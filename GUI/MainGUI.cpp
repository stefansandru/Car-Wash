
#pragma once
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <utility>
#include <vector>
#include <string>
#include "../SErvice/service.h"
#include "CarWashGUI.h"
#include "RaportGUI.h"
#include "MainGUI.h"
#include "CarsTableModel.h"
#include "../Exceptions/RepoException.h"
#include "../Exceptions/ValidateException.h"


using std::vector;
using std::string;

void MainGUI::initGUI() {
    tableCars->setMinimumSize(520, 300);
    tableCars->setSelectionBehavior(QAbstractItemView::SelectRows);

    auto* MainLayout = new QHBoxLayout{};
    setLayout(MainLayout);
    MainLayout->addLayout(getCarsListLayout());
    MainLayout->addWidget(getVLine());
    MainLayout->addLayout(getCRUDOperaitionsLayout());
}

QVBoxLayout *MainGUI::getCRUDOperaitionsLayout() {
    auto CRUDOpeationsLayout = new QVBoxLayout;
    CRUDOpeationsLayout->addLayout(getAddModifyDeleteForm());
    CRUDOpeationsLayout->addLayout(getAddModifyDeleteMenu());
    CRUDOpeationsLayout->addWidget(getHLine());
    CRUDOpeationsLayout->addWidget(new QLabel{"Type to search for cars:"});
    CRUDOpeationsLayout->addLayout(getSearchForm());
    CRUDOpeationsLayout->addWidget(getHLine());
    CRUDOpeationsLayout->addLayout(getLastMenu());
    return CRUDOpeationsLayout;
}

QHBoxLayout *MainGUI::getLastMenu() {
    auto meniu = new QHBoxLayout;
    meniu->addWidget(btnCarWash);
    meniu->addWidget(btnTypeRaport);
    meniu->addWidget(btnExit);
    btnCarWash->setStyleSheet("background-color: #003d99;"
                              " color: white;"
                              " border: 1px solid black; "
                              "border-radius: 5px;"
                              " height: 18px;");
    btnExit->setStyleSheet("background-color: #b30000;"
                           " color: white; border: 1px solid black; "
                           "border-radius: 5px;"
                           " height: 17px;");
    return meniu;
}

QFormLayout *MainGUI::getSearchForm() {
    auto SearchFrom = new QFormLayout;
    SearchFrom->addRow("Registration", lineSearchRegistration);
    SearchFrom->addRow("Producer", lineSearchProducer);
    SearchFrom->addRow("Model", lineSearchModel);
    SearchFrom->addRow("Type", lineSearchType);
    return SearchFrom;
}

QFrame *MainGUI::getHLine() {
    auto* HLine1 = new QFrame();
    HLine1->setFrameShape(QFrame::HLine);
    HLine1->setLineWidth(1 / 4);
    HLine1->setStyleSheet("color: gray;");
    return HLine1;
}

QHBoxLayout *MainGUI::getAddModifyDeleteMenu() {
    auto AddModifydeleteMenu = new QHBoxLayout;
    AddModifydeleteMenu->addWidget(btnAdd);
    AddModifydeleteMenu->addWidget(btnDelete);
    AddModifydeleteMenu->addWidget(btnModify);
    AddModifydeleteMenu->addWidget(btnUndo);
    return AddModifydeleteMenu;
}

QFormLayout *MainGUI::getAddModifyDeleteForm() {
    auto AddModifyDeleteForm = new QFormLayout;
    AddModifyDeleteForm->addRow("Registration", lineCRUDRegistration);
    AddModifyDeleteForm->addRow("Producer", lineCRUDProducer);
    AddModifyDeleteForm->addRow("Model", lineCRUDModel);
    AddModifyDeleteForm->addRow("Type", chooseType);
    chooseType->addItem("Sedan");
    chooseType->addItem("SUV");
    chooseType->addItem("Coupe");
    return AddModifyDeleteForm;
}

QFrame *MainGUI::getVLine() {
    auto* Vline = new QFrame();
    Vline->setFrameShape(QFrame::VLine);
    Vline->setLineWidth(1/4);
    Vline->setStyleSheet("color: gray;");
    return Vline;
}

QVBoxLayout *MainGUI::getCarsListLayout() {
    auto* layoutCarsList = new QVBoxLayout{};
    auto* sortingMenu = new QHBoxLayout{};
    sortingMenu->addWidget(new QLabel{"See all cars sorted by:" });
    sortingMenu->addWidget(btnSortRegistration);
    sortingMenu->addWidget(btnSortByProducerModel);
    sortingMenu->addWidget(btnSortByType);

    layoutCarsList->addWidget(new QLabel{
                                         "You can <u>select a car </u>to delete or modify it.<br>"});
    layoutCarsList->addWidget(tableCars);
    layoutCarsList->addLayout(sortingMenu);
    return layoutCarsList;
}

void MainGUI::loadData(const vector<Car>& cars) {
    auto* model = dynamic_cast<CarsTableModel*>(tableCars->model());
    if (model) {
        model->setCars(cars);
    } else {
        model = new CarsTableModel(cars, this);
        tableCars->setModel(model);
    }
}

void MainGUI::initConnect() {
    connectSelectionModel();
    connectSearchFields();
    connectButtons();
}

void MainGUI::connectSelectionModel() {
    QObject::connect(tableCars->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainGUI::onCarSelected);
}

void MainGUI::connectSearchFields() {
    auto connectSearchField = [&](QLineEdit* lineEdit) {
        QObject::connect(lineEdit, &QLineEdit::textChanged, this, [&]() {
            auto registration = lineSearchRegistration->text().toStdString();
            auto producer = lineSearchProducer->text().toStdString();
            auto carModel = lineSearchModel->text().toStdString();
            auto type = lineSearchType->text().toStdString();
            loadData(serv.filterCars(registration, producer, carModel, type));
        });
    };

    connectSearchField(lineSearchRegistration);
    connectSearchField(lineSearchProducer);
    connectSearchField(lineSearchModel);
    connectSearchField(lineSearchType);
}

void MainGUI::connectButtons() {
    QObject::connect(btnExit, &QPushButton::clicked, this, &MainGUI::close);

    QObject::connect(btnAdd, &QPushButton::clicked, this, &MainGUI::onAddButtonClicked);
    QObject::connect(btnDelete, &QPushButton::clicked, this, &MainGUI::onDeleteButtonClicked);
    QObject::connect(btnModify, &QPushButton::clicked, this, &MainGUI::onModifyButtonClicked);
    QObject::connect(btnUndo, &QPushButton::clicked, this, &MainGUI::onUndoButtonClicked);

    QObject::connect(btnCarWash, &QPushButton::clicked, this, &MainGUI::onCarWashButtonClicked);
    QObject::connect(btnTypeRaport, &QPushButton::clicked, this, &MainGUI::onRaportButtonClicked);

    QObject::connect(btnSortRegistration, &QPushButton::clicked, this, &MainGUI::onSortRegistrationButtonClicked);
    QObject::connect(btnSortByProducerModel, &QPushButton::clicked, this, &MainGUI::onSortByProducerModelButtonClicked);
    QObject::connect(btnSortByType, &QPushButton::clicked, this, &MainGUI::onSortByTypeButtonClicked);
}

void MainGUI::onAddButtonClicked() {
    try {
        auto registration = lineCRUDRegistration->text().toStdString();
        auto producer = lineCRUDProducer->text().toStdString();
        auto model = lineCRUDModel->text().toStdString();
        auto type = chooseType->currentText().toStdString();

        serv.add_srv(registration, producer, model, type);
        loadData(serv.get_all_cars_srv());

        QMessageBox::information(this, "Information", "Car added successfully!\n"
                                                      "Check the last row in the list to view the newly added car. ");
    } catch (const ValidateException &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
    } catch (const RepoException &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
    }
}

void MainGUI::onDeleteButtonClicked() {
    try {
        auto registration = lineCRUDRegistration->text().toStdString();
        serv.delete_car_srv(registration);
        loadData(serv.get_all_cars_srv());

    } catch (RepoException &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
    }
}

void MainGUI::onModifyButtonClicked() {
    try {
        auto old_registration = lineCRUDRegistration->text().toStdString();
        auto registration = lineCRUDRegistration->text().toStdString();
        auto producer = lineCRUDProducer->text().toStdString();
        auto model = lineCRUDModel->text().toStdString();
        auto type = chooseType->currentText().toStdString();

        serv.modify_car_srv(old_registration, registration, producer, model, type);
        loadData(serv.get_all_cars_srv());

    } catch (ValidateException &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
    } catch (RepoException &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
    }
}

void MainGUI::onUndoButtonClicked() {
    try {
        serv.undo_srv();
        loadData(serv.get_all_cars_srv());
    } catch (UndoExceptions &e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_message()));
    }
}

void MainGUI::onCarWashButtonClicked() {
    auto gui = new CarWashGUI{ serv };
    gui->show();
}

void MainGUI::onRaportButtonClicked() {
    auto gui = new RaportGUI{ serv };
    gui->show();
}

void MainGUI::onSortRegistrationButtonClicked() {
    loadData(serv.registration_sort());
}

void MainGUI::onSortByProducerModelButtonClicked() {
    loadData(serv.producer_and_model_sort());
}

void MainGUI::onSortByTypeButtonClicked() {
    loadData(serv.type_sort());
}

void MainGUI::onCarSelected() {
    auto selectedIndexes = tableCars->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto registration = selectedIndexes.at(1).data().toString();
    auto producer = selectedIndexes.at(2).data().toString();
    auto model = selectedIndexes.at(3).data().toString();
    auto type = selectedIndexes.at(4).data().toString();

    lineCRUDRegistration->setText(registration);
    lineCRUDProducer->setText(producer);
    lineCRUDModel->setText(model);
    chooseType->setCurrentText(type);
}
