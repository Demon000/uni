#include <cassert>
#include <exception>
#include <unordered_map>

#include "entities/Tenant.h"
#include "repositories/TenantRepository.h"
#include "repositories/NotificationRepository.h"
#include "services/TenantService.h"

using std::vector;
using std::exception;
using std::unordered_map;

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
    TenantRepository repository{"tenants_test_tenant_repository.csv"};
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

void test_notification_repository() {
    NotificationRepository notificationRepository{"notifications_test_notification_repository.csv"};
    vector<int> numbers;

    notificationRepository.addNumber(1);
    notificationRepository.addNumber(2);
    notificationRepository.addNumber(3);

    try {
        notificationRepository.numberExists(4);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    numbers = notificationRepository.getNumbers();
    assert(numbers[0] == 1);
    assert(numbers[1] == 2);
    assert(numbers[2] == 3);

    notificationRepository.removeNumber(1);
    try {
        notificationRepository.numberExists(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    try {
        notificationRepository.removeNumber(4);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    notificationRepository.removeNumbers();
    numbers = notificationRepository.getNumbers();
    assert(numbers.size() == 0);
}
void test_tenant_service() {
    TenantRepository repository{"tenants_test_tenant_service.csv"};
    NotificationRepository notificationRepository{"notifications_test_tenant_service.csv"};
    TenantService service{repository, notificationRepository};
    std::vector<Tenant> tenants;
    Tenant retrieved;

    const Tenant first = service.createTenant(1,  "Cristi", 20, "studio");
    const Tenant second = service.createTenant(2, "Gigi", 200, "penthouse");
    const Tenant third = service.createTenant(3, "Marian", 300, "penthouse");
    const Tenant forth = service.createTenant(4, "Gabriel", 20, "basement");

    unordered_map<int, int> surfaceReport = service.getSurfaceReport();
    assert(surfaceReport[20] == 2);
    assert(surfaceReport[200] == 1);
    assert(surfaceReport[300] == 1);

    tenants = service.getFilteredTenants("1");
    assert(tenants.size() == 1);
    tenants = service.getFilteredTenants("Cristi");
    assert(tenants.size() == 1);
    tenants = service.getFilteredTenants("20");
    assert(tenants.size() == 3);
    tenants = service.getFilteredTenants("studio");
    assert(tenants.size() == 1);

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

    tenants = service.getTenants();
    assert(tenants[0] == first);
    assert(tenants[1] == second);
    assert(tenants[2] == third);
    assert(tenants[3] == forth);

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

    service.addNotification(1);
    service.addNotification(2);
    service.addNotification(3);

    tenants = service.getTenantsToNotify();
    assert(tenants[0] == first);
    assert(tenants[1] == second);
    assert(tenants[2] == third);
    assert(service.getNumberOfNotifications() == 3);

    try {
        service.addNotification(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    try {
        service.addNotification(5);
        assert(false);
    } catch (exception&) {
        assert(true);
    }

    service.addRandomNotifications(3);
    assert(service.getNumberOfNotifications() == 3);

    service.removeNotifications();
    assert(service.getNumberOfNotifications() == 0);

    service.addNotification(2);
    service.removeTenant(1);
    try {
        service.getTenant(1);
        assert(false);
    } catch (exception&) {
        assert(true);
    }
}

void test_tenant_service_undo() {
    TenantRepository repository{"tenants_test_tenant_service_undo.csv"};
    NotificationRepository notificationRepository{"notifications_test_tenant_service_undo.csv"};
    TenantService service{repository, notificationRepository};
    std::vector<Tenant> tenants;
    Tenant retrieved;

    const Tenant first = service.createTenant(1,  "Cristi", 20, "studio");
    const Tenant second = service.createTenant(2, "Gigi", 200, "penthouse");
    const Tenant third = service.createTenant(3, "Marian", 300, "penthouse");
    const Tenant forth = service.createTenant(4, "Gabriel", 20, "basement");

    tenants = service.getTenants();
    assert(tenants.size() == 4);

    service.undo();
    tenants = service.getTenants();
    assert(tenants.size() == 3);

    service.updateTenant(3, "NotMarian");
    retrieved = service.getTenant(3);
    assert(retrieved.getName() == "NotMarian");

    service.undo();
    retrieved = service.getTenant(3);
    assert(retrieved.getName() == "Marian");

    service.removeTenant(3);
    tenants = service.getTenants();
    assert(tenants.size() == 2);

    service.undo();
    tenants = service.getTenants();
    assert(tenants.size() == 3);

    try {
        while (true) {
            service.undo();
        }
        assert(false);
    } catch (exception&) {
        assert(true);
    }
}

int main() {
    test_tenant();
    test_tenant_repository();
    test_notification_repository();
    test_tenant_service();
    test_tenant_service_undo();

    return 0;
}
