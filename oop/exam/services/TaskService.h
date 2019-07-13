#include <vector>
#include <string>
#include <algorithm>

#include "../entities/Task.h"
#include "../validators/TaskValidator.h"
#include "../repositories/TaskRepository.h"
#include "../observe/Observe.h"

#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

class TaskService : public Observable {
public:
    /*
     * Create a task service.
     *
     * @param repository (TaskRepository) The repository to use for data storage.
     */
    TaskService(TaskRepository& repository, TaskValidator& validator)
            : repository{repository}, validator{validator} {}

    /*
     * Get the tasks in the service, sorted by state.
     *
     * @return (std::vector<Task>) The tasks in the repository, sorted by state.
     */
    std::vector<Task> getTasks() const {
        std::vector<Task> tasks = repository.getTasks();
        std::sort(tasks.begin(), tasks.end(), [](const Task& first, const Task& second) {
            return first.getState() < second.getState();
        });

        return tasks;
    }

    /*
     * Get the tasks in the service, sorted by state and filtered by programmer name.
     *
     * @param part (std::string) The part of the programmer name to look for.
     *
     * @return (std::vector<Task>) The tasks in the repository, sorted by state
     *      and filtered by programmer name.
     */
    std::vector<Task> getFilteredTasks(std::string part) const {
        std::vector<Task> tasks = getTasks();
        std::vector<Task> matchingTasks;

        for (const Task& task : tasks) {
            if (task.isProgrammer(part)) {
                matchingTasks.push_back(task);
            }
        }

        return matchingTasks;
    }

    /*
     * Add a task to the service.
     *
     * @param id (int) The id of the new task.
     * @param description (std::string) The description of the new task.
     * @param state (std::string) The state of the new task.
     * @param programmers (std::vector<std::string>) The programmers working on the new task.
     */
    void addTask(int id, std::string description,
            std::string state, std::vector<std::string> programmers) {
        Task task{id, description, state, programmers};
        validator.validate(task);
        repository.addTask(task);
        notify(ObserveEvent::CHANGE);
    }

    /*
     * Update the state of a task.
     *
     * @param id (int) The id of the task.
     * @param state (std::string) The new state of the task.
     */
    void updateTask(int id, std::string state) {
        validator.validateState(state);
        Task task = repository.getTaskById(id);
        repository.updateTaskState(task, state);
        notify(ObserveEvent::CHANGE);
    }

private:
    TaskRepository& repository;
    TaskValidator& validator;
};

#endif // TASK_SERVICE_H
