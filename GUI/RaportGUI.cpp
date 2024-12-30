
#include "RaportGUI.h"
#include <QVBoxLayout>
#include <QStandardItemModel>

void RaportGUI::initGUI() {
    auto* lyMain = new QVBoxLayout;
    setLayout(lyMain);

    lyMain->addWidget(tableTypeAndCarsCount);
    lyMain->addWidget(btnExit);
}

void RaportGUI::loadTable(const map<string, CarTypeCountDTO>& typeAndCarsCount) {
    auto* model = new QStandardItemModel(static_cast<int>(typeAndCarsCount.size()), 2, this);
    QStringList headers;
    headers << "Type" << "Number of cars";

    int row = 0;
    for (const auto& pair : typeAndCarsCount) {
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(pair.first)));
        model->setItem(row, 1, new QStandardItem(QString::number(pair.second.get_nr())));
        row++;
    }
    tableTypeAndCarsCount->setModel(model);
}

void RaportGUI::initConnect() {
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        close();
    });
}