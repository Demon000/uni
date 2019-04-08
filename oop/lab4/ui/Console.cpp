#include <string>
#include <iostream>
#include <exception>

#include "Console.h"

using std::string;
using std::cin;
using std::cout;
using std::exception;

Console::Console(TenantService& service) : service(service) {}

void Console::addTenants() {
    service.createTenant(1,  "Cristi", 20, "studio");
    service.createTenant(2, "Gigi", 200, "penthouse");
    service.createTenant(3, "Marian", 300, "penthouse");
    service.createTenant(4, "Gabriel", 20, "basement");
}

int Console::readInt(const string& message) {
	int value;
	cout << message << ": ";
	cin >> value;
	return value;
}

string Console::readStr(const string& message) {
	string value;
	cout << message << ": ";
	cin >> value;
	return value;
}

void Console::printTenant(const Tenant& tenant, const string& message) {
	cout << message << ":\n";
	cout << tenant.toString() << "\n";
}

void Console::printTenants(const List<Tenant>& tenants, const string& message) {
	cout << message << ":\n";
	tenants.for_each([](const Tenant& tenant) {
		cout << tenant.toString() << "\n";
		return false;
	});
}

void Console::addTenant() {
	int number = readInt("Number");
	string name = readStr("Name");
	int surface = readInt("Surface");
	string type = readStr("Type");

	try {
		const Tenant& tenant = service.createTenant(number, name, surface, type);
		printTenant(tenant, "Added tenant");
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

void Console::showTenants() {
	List<Tenant> tenants = service.getTenants();
	printTenants(tenants, "Tenants");
}

void Console::findApartment() {
	int number = readInt("Number");

	try {
		const Tenant& tenant = service.getTenant(number);
		printTenant(tenant, "Found tenant");
	} catch (exception&) {
		cout << "Tenant does not exist.\n";
	}
}

void Console::filterApartments() {
	List<Tenant> tenants;
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

void Console::sortApartments() {
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

	List<Tenant> tenants = service.getTenantsSortedBy(sortType);
	printTenants(tenants, "Sorted tenants");
}

void Console::goodbye() {
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
	case 0:
		goodbye();
		break;
	default:
		cout << "Option is invalid.\n";
		break;
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
