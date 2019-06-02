#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"

#ifndef TENANTS_TABLE_H
#define TENANTS_TABLE_H

class TenantsTable : public QTableWidget {
public:
    TenantsTable(ObservableTenantService& service) : service{service} {
        setColumnCount(5);

        setSortingEnabled(true);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalHeader()->hide();
        setHorizontalHeaderLabels(QStringList{"Number", "Name", "Surface", "Type", "Same surface"});
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    int selectedTenantNumber() {
        QList<QTableWidgetItem*> items = selectedItems();

        for (QTableWidgetItem* item : items) {
            if (item->column() == 0) {
                QString text = item->text();
                int number = text.toInt();
                return number;
            }
        }

        return -1;
    }



    void showTenants(std::vector<Tenant> tenants) {
        std::unordered_map<int, int> surfaceReport = service.getSurfaceReport();

        int rows = tenants.size();
        setRowCount(rows);

        QBrush background;
        if (rows < 5) {
            background = Qt::red;
        }

        int row = 0;
        for (const Tenant& tenant : tenants) {
            QTableWidgetItem* item;
            QString text;

            item = new QTableWidgetItem();
            item->setData(Qt::DisplayRole, tenant.getNumber());
            item->setBackground(background);
            setItem(row, 0, item);

            text = QString::fromStdString(tenant.getName());
            item = new QTableWidgetItem(text);
            item->setBackground(background);
            setItem(row, 1, item);

            item = new QTableWidgetItem();
            item->setData(Qt::DisplayRole, tenant.getSurface());
            item->setBackground(background);
            setItem(row, 2, item);

            text = QString::fromStdString(tenant.getType());
            item = new QTableWidgetItem(text);
            item->setBackground(background);
            setItem(row, 3, item);

            text = QString::number(surfaceReport[tenant.getSurface()]);
            item = new QTableWidgetItem(text);
            item->setBackground(background);
            setItem(row, 4, item);

            row++;
        }
    }

private:
    ObservableTenantService& service;
};

#endif // TENANTS_TABLE_H
