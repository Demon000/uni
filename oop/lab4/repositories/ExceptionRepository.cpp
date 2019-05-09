#include <cstdlib>

#include "ExceptionRepository.h"

ExceptionRepository::ExceptionRepository(double chance) : chance{chance} {}

void ExceptionRepository::addTenant(const Tenant& tenant) {
    srand((unsigned)time(NULL));
    double current = ((double)rand() / (double)RAND_MAX);
    if (current < chance) {
        throw ExceptionChance();
    }

    BaseRepository::addTenant(tenant);
}
