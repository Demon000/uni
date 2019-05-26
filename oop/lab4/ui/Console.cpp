#include <string>
#include <iostream>
#include <exception>
#include <limits>
#include <unordered_map>

#include "Console.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::exception;
using std::numeric_limits;
using std::streamsize;
using std::unordered_map;

Console::Console(TenantService& service) : service(service) {}

void Console::addTenants() {
    try {
        service.createTenant(1,  "Cristi", 20, "studio", true);
    } catch (exception&) {}

    try {
        service.createTenant(2, "Gigi", 200, "penthouse", true);
    } catch (exception&) {}

    try {
        service.createTenant(3, "Marian", 300, "penthouse", true);
    } catch (exception&) {}

    try {
        service.createTenant(4, "Gabriel", 20, "basement", true);
    } catch (exception&) {}
}

int Console::readInt(const string& message) const {
    int value;

    while (true) {
        cout << message << ": ";
        cin >> value;

        if (cin) {
            break;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number." << "\n";
    }

    return value;
}

string Console::readStr(const string& message) const {
    string value;
    cout << message << ": ";
    cin >> value;
    return value;
}

void Console::printTenant(const Tenant& tenant, const string& message) const {
    cout << message << ":\n";
    cout << tenant.toString() << "\n";
}

void Console::printTenants(vector<Tenant> tenants, const string& message) const {
    cout << message << ":\n";

    if (!tenants.size()) {
        cout << "No tenants!\n";
        return;
    }

    for(const auto& tenant : tenants) {
        cout << tenant.toString() << "\n";
    }
}

void Console::addTenant() {
    int number = readInt("Number");
    string name = readStr("Name");
    int surface = readInt("Surface");
    string type = readStr("Type");

    try {
        const Tenant& tenant = service.createTenant(number, name, surface, type);
        printTenant(tenant, "Added tenant");
    } catch (ExceptionChance&) {
        cout << "Tenant addition failed by chance.\n";
    } catch (exception&) {
        cout << "Tenant already exists.\n";
    }
}

void Console::updateTenant() {
    int number = readInt("Number");
    string name = readStr("New name");

    try {
        const Tenant& tenant = service.updateTenant(number, name);
        printTenant(tenant, "Updated tenant");
    } catch (exception&) {
        cout << "Tenant does not exist.\n";
    }
}

void Console::deleteTenant() {
    int number = readInt("Number");

    try {
        const Tenant& tenant = service.removeTenant(number);
        printTenant(tenant, "Delated tenant");
    } catch (exception&) {
        cout << "Tenant does not exist.\n";
    }
}

void Console::showTenants() const {
    vector<Tenant> tenants = service.getTenants();
    printTenants(tenants, "Tenants");
}

void Console::findApartment() const {
    int number = readInt("Number");

    try {
        const Tenant& tenant = service.getTenant(number);
        printTenant(tenant, "Found tenant");
    } catch (exception&) {
        cout << "Tenant does not exist.\n";
    }
}

void Console::filterApartments() const {
    vector<Tenant> tenants;
    string type;
    int surface;

    cout << "Filter by:\n"
            "1. Type\n"
            "2. Surface\n";

    int option = readInt("Filter by");

    switch (option) {
    case 1:
        type = readStr("Type");
        tenants = service.getTenantsByType(type);
        break;
    case 2:
        surface = readInt("Surface");
        tenants = service.getTenantsBySurface(surface);
        break;
    default:
        cout << "Filter type invalid.\n";
        break;
    }

    printTenants(tenants, "Filtered tenants");
}

void Console::sortApartments() const {
    cout << "Sort types:\n"
            "1. Sort by name\n"
            "2. Sort by surface\n"
            "3. Sort by type and surface\n";

    int option = readInt("Sort type");
    TenantSortType sortType;

    switch (option) {
    case 1:
        sortType = TenantSortType::SortByName;
        break;
    case 2:
        sortType = TenantSortType::SortBySurface;
        break;
    case 3:
        sortType = TenantSortType::SortByTypeAndSurface;
        break;
    default:
        cout << "Sort type invalid.\n";
        return;
    }

    vector<Tenant> tenants = service.getTenantsSortedBy(sortType);
    printTenants(tenants, "Sorted tenants");
}

void Console::addNotifiedApartment() const {
    int number = readInt("Number");

    try {
        service.addNotification(number);
    } catch (NumberExistsException&) {
        cout << "Apartment already added.\n";
    } catch (TenantMissingException&) {
        cout << "Tenant does not exist.\n";
    }
}

void Console::showNotifiedTenats() const {
    vector<Tenant> tenants = service.getTenantsToNotify();
    printTenants(tenants, "Tenants to be notified");
}

void Console::deleteNotifiedApartments() const {
    service.removeNotifications();
}

void Console::generateNotifiedApartments() const {
    int number = readInt("Number of tenants");

    service.addRandomNotifications(number);
    showNotifiedTenats();
}

void Console::undo() {
    try {
        service.undo();
    } catch (exception&) {
        cout << "Nothing left to undo!\n";
    }
}

void Console::showSurfaceReport() const {
    unordered_map<int, int> surfaceReport = service.getSurfaceReport();

    for (auto& it: surfaceReport) {
        cout << it.second << " apartments have a surface of " << it.first << "mp.\n";
    }
}

void Console::goodbye() const {
    cout << "Goodbye!\n";
}

int Console::askOption() {
    cout << "Options:\n"
            "1. Add tenant\n"
            "2. Update tenant\n"
            "3. Delete tenant\n"
            "4. Show tenants\n"
            "5. Find apartment\n"
            "6. Show filtered apartments\n"
            "7. Show sorted apartments\n"
            "8. Add notified apartment\n"
            "9. Generate notified apartments\n"
            "10. Delete all notified apartments\n"
            "11. Show notified tenants\n"
            "12. Undo the last action\n"
            "13. Show surface report\n"
            "0. Exit\n";

    int option = readInt("Option");

    switch (option) {
    case 1:
        addTenant();
        break;
    case 2:
        updateTenant();
        break;
    case 3:
        deleteTenant();
        break;
    case 4:
        showTenants();
        break;
    case 5:
        findApartment();
        break;
    case 6:
        filterApartments();
        break;
    case 7:
        sortApartments();
        break;
    case 8:
        addNotifiedApartment();
        break;
    case 9:
        generateNotifiedApartments();
        break;
    case 10:
        deleteNotifiedApartments();
        break;
    case 11:
        showNotifiedTenats();
        break;
    case 12:
        undo();
        break;
    case 13:
        showSurfaceReport();
        break;
    case 0:
        goodbye();
        break;
    default:
        cout << "Option is invalid.\n";
        break;
    }

    if (option != 0) {
        int numberOfNotifications = service.getNumberOfNotifications();
        cout << "Number of apartments to be notified: "
                << numberOfNotifications << "\n";
    }

    return option;
}

void Console::run() {
    addTenants();

    int option = -1;
    while (option != 0) {
        option = askOption();
    }
}
