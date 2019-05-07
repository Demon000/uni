#include <vector>
#include <string>

#ifndef NOTIFICATION_REPOSITORY_H
#define NOTIFICATION_REPOSITORY_H

class NotificationRepository {
public:
    NotificationRepository(const std::string&);

    /**
     * Add an apartment number to the repository.
     *
     * @param number The apartment number.
     */
    void addNumber(int) const;

    /**
     * Check if an apartment number is already on the notification list.
     *
     * @param number The apartment number to check.
     */
    void numberExists(int) const;

    /**
     * Get all the apartment numbers to be notified.
     *
     * @return The apartments numbers to be notified.
     */
    std::vector<int> getNumbers() const;

    /**
     * Remove an apartment number from the notification list.
     */
    void removeNumber(int) const;

    /**
     * Remove all the apartment numbers from the notification list.
     */
    void removeNumbers() const;

private:
    /**
     * Read the numbers from the storage file.
     *
     * @return The numbers read.
     */
    std::vector<int> readNumbers() const;

    /**
     * Write numbers to the storage file.
     *
     * @param numbers The numbers to write.
     */
    void writeNumbers(const std::vector<int>&) const;

    std::string path;
};

class NumberMissingException : public std::exception {};
class NumberExistsException : public std::exception {};

#endif
