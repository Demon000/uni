#include <vector>

#ifndef NOTIFICATION_REPOSITORY_H
#define NOTIFICATION_REPOSITORY_H

class NotificationRepository {
public:
    /**
     * Add an apartment number to the repository.
     *
     * @param number The apartment number.
     */
    void addNumber(int);

    /**
     * Check if an apartment number is already on the notification list.
     *
     * @param number The apartment number to check.
     */
    void getTenantByNumber(int);

    /**
     * Get all the apartment numbers to be notified.
     *
     * @return The apartments numbers to be notified.
     */
    std::vector<int>& getNumbers();

    /**
     * Remove an apartment number from the notification list.
     */
    void removeNumber(int);

    /**
     * Remove all the apartment numbers from the notification list.
     */
    void removeNumbers();

private:
    std::vector<int> numbers;
};

class NumberMissingException : public std::exception {};
class NumberExistsException : public std::exception {};

#endif
