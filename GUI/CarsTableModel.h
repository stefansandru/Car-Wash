
#ifndef CARWASH_CARSTABLEMODEL_H
#define CARWASH_CARSTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "../Domain/car.h"

class CarsTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    std::vector<Car> cars;

public:
    explicit CarsTableModel(const std::vector<Car>& cars, QObject* parent = nullptr)
        : QAbstractTableModel(parent), cars(cars) {}

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return static_cast<int>(cars.size());
    }

    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5; // Row number, Registration, Producer, Model, Type
    }

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return {};
        }

        const auto& car = cars[index.row()];
        switch (index.column()) {
            case 0: return index.row() + 1; // Numărul rândului
            case 1: return QString::fromStdString(car.get_registration());
            case 2: return QString::fromStdString(car.get_producer());
            case 3: return QString::fromStdString(car.get_model());
            case 4: return QString::fromStdString(car.get_type());
            default: return {};
        }
    }

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
            return {};
        }

        switch (section) {
            case 0: return "Row Number";
            case 1: return "Registration";
            case 2: return "Producer";
            case 3: return "Model";
            case 4: return "Type";
            default: return {};
        }
    }

    void setCars(const std::vector<Car>& newCars) {
        beginResetModel();
        cars = newCars;
        endResetModel();
    }
};

#endif //CARWASH_CARSTABLEMODEL_H
