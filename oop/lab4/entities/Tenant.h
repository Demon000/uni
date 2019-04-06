#include <string>

#ifndef TENANT_H
#define TENANT_H

class Tenant {
public:
    Tenant(int, std::string, int, std::string);

    std::string toString() const;

    int getNumber() const;
    const std::string& getName() const;
    int getSurface() const;
    const std::string& getType() const;

    void setName(std::string);

private:
    int number;
    std::string name;
    int surface;
    std::string type;
};

#endif // TENANT_H
