#include <iostream>
#include <cassert>
#include <exception>

#include "list/List.h"
#include "entities/Tenant.h"
#include "repositories/TenantRepository.h"
#include "services/TenantService.h"

using std::exception;

void test_list() {
    List<int> l;

    l.push_back(3);
    l.push_back(30);
    l.push_back(5);
    l.push_back(1);
    l.sort([](int first, int second) {
        return first < second;
    });

    assert(l[0] == 1);
    assert(l[1] == 3);
    assert(l[2] == 5);
    assert(l[3] == 30);

    l.for_each([](int i) {
        if (i == 3) {
            return true;
        }

        return false;
    });
}

void test_tenant() {
    Tenant tenant{1,  "Cristi", 1, "studio"};

    assert(tenant.getNumber() == 1);
    assert(tenant.getName() == "Cristi");
    assert(tenant.getSurface() == 1);
    assert(tenant.getType() == "studio");

    tenant.setName("George");
    assert(tenant.getName() == "George");

    assert(tenant.toString() == "Number: 1, Name: George, Surface: 1mp, Type: studio");
}

void test_tenant_repository() {
    TenantRepository repository;
    std::vector<Tenant> tenants;
    Tenant retrieved;

    const Tenant first{1,  "Cristi", 20, "studio"};
    repository.addTenant(first);

    const Tenant second{2, "Gigi", 200, "penthouse"};
    repository.addTenant(second);

    const Tenant third{3, "Marian", 300, "penthouse"};
    repository.addTenant(third);

    const Tenant forth{4, "Gabriel", 20, "basement"};
    repository.addTenant(forth);

    retrieved = repository.getTenantByNumber(1);
    assert(retrieved == first);

    try {
        repository.getTenantByNumber(5);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    tenants = repository.getTenantsBySurface(20);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);

    tenants = repository.getTenantsByType("penthouse");
    assert(tenants[0] == second);
    assert(tenants[1] == third);

    retrieved = repository.getTenantByNumber(1);
    repository.updateTenant(retrieved, "George");
    assert(retrieved.getName() == "George");
    retrieved = repository.getTenantByNumber(1);
    assert(retrieved.getName() == "George");

    retrieved = repository.getTenantByNumber(1);
    repository.removeTenant(retrieved);

    try {
        repository.getTenantByNumber(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    try {
        repository.updateTenant(retrieved, "Broken");
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    try {
        repository.removeTenant(retrieved);
        assert(false);
    } catch (exception&) {
        assert(true);
    }
}

void test_tenant_service() {
    TenantRepository repository;
    TenantService service{repository};
    std::vector<Tenant> tenants;
    Tenant retrieved;

    const Tenant first = service.createTenant(1,  "Cristi", 20, "studio");
    const Tenant second = service.createTenant(2, "Gigi", 200, "penthouse");
    const Tenant third = service.createTenant(3, "Marian", 300, "penthouse");
    const Tenant forth = service.createTenant(4, "Gabriel", 20, "basement");

    try {
        service.createTenant(1,  "", 0, "");
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    retrieved = service.getTenant(1);
    assert(retrieved == first);

    try {
        service.getTenant(5);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    tenants = service.getTenantsBySurface(20);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);

    tenants = service.getTenantsByType("penthouse");
    assert(tenants[0] == second);
    assert(tenants[1] == third);

    tenants = service.getTenantsSortedBy(TenantSortType::SortByName);
    assert(tenants[0] == first);
    assert(tenants[1] == forth);
    assert(tenants[2] == second);
    assert(tenants[3] == third);

    tenants = service.getTenantsSortedBy(TenantSortType::SortByType);
    assert(tenants[0] == forth);
    assert(tenants[1] == second || tenants[1] == third);
    assert(tenants[2] == second || tenants[2] == third);
    assert(tenants[3] == first);

    tenants = service.getTenantsSortedBy(TenantSortType::SortBySurface);
    assert(tenants[0] == first || tenants[0] == forth);
    assert(tenants[1] == first || tenants[1] == forth);
    assert(tenants[2] == second);
    assert(tenants[3] == third);

    tenants = service.getTenantsSortedBy(TenantSortType::SortByTypeAndSurface);
    assert(tenants[0] == forth);
    assert(tenants[1] == second);
    assert(tenants[2] == third);
    assert(tenants[3] == first);

    retrieved = service.updateTenant(1, "George");
    assert(retrieved.getName() == "George");
    retrieved = service.getTenant(1);
    assert(retrieved.getName() == "George");

    service.removeTenant(1);
    try {
        service.getTenant(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }
}

int main() {
    test_list();
    test_tenant();
    test_tenant_repository();
    test_tenant_service();

    return 0;
}
