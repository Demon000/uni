#include <string>
#include <vector>
#include <algorithm>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"

#ifndef TENANTS_TABLE_H
#define TENANTS_TABLE_H

class TenantsTableModel : public QAbstractTableModel {

public:
    TenantsTableModel() {}

    int rowCount(const QModelIndex&) const {
        return tenants.size();
    }

    int columnCount(const QModelIndex&) const {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role) const {
        if (role != Qt::DisplayRole) {
            return QVariant();
        }

        int row = index.row();
        int column = index.column();
        const Tenant& tenant = tenants[row];

        switch (column) {
        case 0:
            return tenant.getNumber();
        case 1:
            return QString::fromStdString(tenant.getName());
        case 2:
            return tenant.getSurface();
        case 3:
            return QString::fromStdString(tenant.getType());
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (role != Qt::DisplayRole) {
            return QVariant();
        }

        if (orientation != Qt::Horizontal) {
            return QVariant();
        }

        switch (section) {
        case 0:
            return "Number";
        case 1:
            return "Name";
        case 2:
            return "Surface";
        case 3:
            return "Type";
        }

        return QVariant();
    }

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) {
        std::sort(tenants.begin(), tenants.end(),
                [&](const Tenant& first, const Tenant& second) {
            bool result = false;

            switch (column) {
            case 0:
                result = first.getNumber() > second.getNumber();
                break;
            case 1:
                result = first.getName() > second.getName();
                break;
            case 2:
                result = first.getSurface() > second.getSurface();
                break;
            case 3:
                result = first.getType() > second.getType();
                break;
            }

            if (order == Qt::DescendingOrder) {
                result = !result;
            }

            return result;
        });
    }

    void populate(std::vector<Tenant> newTenants) {
        emit beginResetModel();
        tenants = newTenants;
        emit endResetModel();
    }

private:
    std::vector<Tenant> tenants;
};

class TenantsTable : public QTableView {
public:
    TenantsTable() {
        model = new TenantsTableModel();
        setModel(model);

        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalHeader()->hide();
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    int selectedTenantNumber() {
        QList<QModelIndex> indexes = selectedIndexes();

        for (QModelIndex index : indexes) {
            if (index.column() == 0) {
                QVariant data = model->data(index, Qt::DisplayRole);
                QString text = data.toString();
                int number = text.toInt();
                return number;
            }
        }

        return -1;
    }

    void showTenants(std::vector<Tenant> tenants) {
        setSortingEnabled(false);
        model->populate(tenants);
        setSortingEnabled(true);
    }

private:
    TenantsTableModel* model;
};

#endif // TENANTS_TABLE_H
