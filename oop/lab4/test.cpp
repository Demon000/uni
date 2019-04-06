#include <iostream>
#include <cassert>
#include <exception>

#include "entities/Tenant.h"
#include "repositories/TenantRepository.h"
#include "services/TenantService.h"

using std::exception;

void test_tenant() {
    Tenant* tenant = new Tenant(1,  "Cristi", 1, "studio");

    assert(tenant->getNumber() == 1);
    assert(tenant->getName() == "Cristi");
    assert(tenant->getSurface() == 1);
    assert(tenant->getType() == "studio");

    tenant->setName("George");
    assert(tenant->getName() == "George");

    assert(tenant->toString() == "Number: 1, Name: George, Surface: 1mp, Type: studio");

    delete tenant;
}

void test_tenant_repository() {
    TenantRepository* repository = new TenantRepository();
    std::vector<Tenant*> tenants;
    Tenant* retrieved;

    Tenant* first = new Tenant(1,  "Cristi", 20, "studio");
    repository->addTenant(first);

    Tenant* second = new Tenant(2, "Gigi", 200, "penthouse");
    repository->addTenant(second);

    Tenant* third = new Tenant(3, "Marian", 300, "penthouse");
    repository->addTenant(third);

    Tenant* forth = new Tenant(4, "Gabriel", 20, "basement");
    repository->addTenant(forth);

    retrieved = repository->getTenantByNumber(1);
    assert(retrieved == first);

    try {
        repository->getTenantByNumber(5);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    tenants = repository->getTenantsBySurface(20);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);

    tenants = repository->getTenantsByType("penthouse");
    assert(tenants[0] == second);
    assert(tenants[1] == third);

    repository->updateTenant(first, "George");
    assert(first->getName() == "George");

    repository->removeTenant(first);
    try {
        repository->getTenantByNumber(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    delete first;
    delete second;
    delete third;
    delete forth;
    delete repository;
}

void test_tenant_service() {
    TenantRepository* repository = new TenantRepository();
    TenantService* service = new TenantService(repository);
    std::vector<Tenant*> tenants;
    Tenant* retrieved;

    Tenant* first = service->createTenant(1,  "Cristi", 20, "studio");
    Tenant* second = service->createTenant(2, "Gigi", 200, "penthouse");
    Tenant* third = service->createTenant(3, "Marian", 300, "penthouse");
    Tenant* forth = service->createTenant(4, "Gabriel", 20, "basement");

    retrieved = service->getTenant(1);
    assert(retrieved == first);

    try {
        service->getTenant(5);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    tenants = service->getTenantsBySurface(20);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);

    tenants = service->getTenantsByType("penthouse");
    assert(tenants[0] == second);
    assert(tenants[1] == third);

    tenants = service->getTenantsSortedBy(TenantSortType::SortByName);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);
    assert(tenants[2] == second);
    assert(tenants[3] == third);

    tenants = service->getTenantsSortedBy(TenantSortType::SortByType);
    assert(tenants[0] == forth);
    assert(tenants[1] == second || tenants[1] == third);
    assert(tenants[2] == second || tenants[2] == third);
    assert(tenants[3] == first);

    tenants = service->getTenantsSortedBy(TenantSortType::SortBySurface);
    assert(tenants[0] == first || tenants[0] == forth);
    assert(tenants[1] == first || tenants[1] == forth);
    assert(tenants[2] == second);
    assert(tenants[3] == third);

    tenants = service->getTenantsSortedBy(TenantSortType::SortByTypeAndSurface);
    assert(tenants[0] == forth);
    assert(tenants[1] == second);
    assert(tenants[2] == third);
    assert(tenants[3] == first);

    retrieved = service->updateTenant(1, "George");
    assert(retrieved == first);
    assert(first->getName() == "George");

    service->removeTenant(1);
    try {
        service->getTenant(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    delete service;
    delete repository;
}

int main() {
    test_tenant();
    test_tenant_repository();
    test_tenant_service();

    return 0;
}
