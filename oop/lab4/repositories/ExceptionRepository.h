#include <vector>
#include <string>
#include <exception>

#include "../entities/Tenant.h"
#include "../repositories/BaseRepository.h"

#ifndef EXCEPTION_REPOSITORY_H
#define EXCEPTION_REPOSITORY_H

class ExceptionChance : public std::exception {};

class ExceptionRepository : public BaseRepository {
public:
    ExceptionRepository(double chance);

    /**
     * Add a tenant.
     *
     * @param tenant The tenant to be added.
     */
    void addTenant(const Tenant&) override;

protected:
    double chance;
};

#endif // EXCEPTION_REPOSITORY_H
