#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../services/TenantService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console(TenantService&);

private:
    TenantService& service;
};

#endif // CONSOLE_H
