#include <string>
#include <sstream>

#include "Tenant.h"

using std::string;
using std::ostringstream;
using std::endl;

Tenant::Tenant(int number, string name, int surface, string type) :
        number{number}, name{name}, surface{surface}, type{type} {}

string Tenant::toString() const {
    ostringstream oss;
    oss << "Number: " << number << ", Name: " << name << ", Surface: "
            << surface << "mp, Type: " << type;
    return oss.str();
}

int Tenant::getNumber() const {
    return number;
}

const string& Tenant::getName() const {
    return name;
}

int Tenant::getSurface() const {
    return surface;
}

const string& Tenant::getType() const {
    return type;
}

void Tenant::setName(string newName) {
    name = newName;
}
