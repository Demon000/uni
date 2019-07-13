#include <vector>
#include <string>
#include <cstring>

#ifndef TASK_H
#define TASK_H

class Task {
public:
    /*
     * Create a task.
     *
     * @param id (int) The id of the new task.
     * @param description (std::string) The description of the new task.
     * @param state (std::string) The state of the new task.
     * @param programmers (std::vector<std::string>) The programmers working on the new task.
     */
    Task(int id, std::string description, std::string state,
            std::vector<std::string> programmers)
            : id{id}, description{description},
                    state{state}, programmers{programmers} {}

    /*
     * Get the task's id.
     *
     * @return (int) The id of the task.
     */
    int getId() const {
        return id;
    }

    /*
     * Get the task's description.
     *
     * @return (std::string) The description of the task.
     */
    const std::string& getDescription() const {
        return description;
    }

    /*
     * Get the task's state.
     *
     * @return (std::string) The state of the task.
     */
    const std::string& getState() const {
        return state;
    }

    /*
     * Get the task's programmers.
     *
     * @return (std::vector<std::string>) The programmers of the task.
     */
    const std::vector<std::string>& getProgrammers() const {
        return programmers;
    }

    /*
     * Get the task's number of programmers.
     *
     * @return (int) The number of programmers of the task.
     */
    int getNumberOfProgrammers() const {
        return programmers.size();
    }

    /*
     * Find whether the given string can be found in the names of the programmers.
     *
     * @return (bool) Whether the given string can be found in the names of the programmers.
     */
    bool isProgrammer(const std::string& part) const {
        const char* cpart = part.c_str();
        for (const std::string& programmer : programmers) {
            const char* cprogrammer = programmer.c_str();
            if (strstr(cprogrammer, cpart) != NULL) {
                return true;
            }
        }

        return false;
    }

    /*
     * Set the state of the task.
     *
     * @param newState (std::string) The new state of the task.
     */
    void setState(const std::string& newState) {
        state = newState;
    }

private:
    int id;
    std::string description;
    std::string state;
    std::vector<std::string> programmers;
};

class TaskExists : public std::exception {};
class TaskMissing : public std::exception {};
class TaskDescriptionMissing : public std::exception {};
class TaskStateWrong : public std::exception {};
class TaskProgrammersNumberWrong : public std::exception {};

#endif // TASK_H
