#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../entities/Task.h"

#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

class TaskRepository {
public:
    /*
     * Create a task repository.
     *
     * @param path (std::string) The path of the file to use for storing the tasks.
     */
    TaskRepository(std::string path) : path{path} {}

    /*
     * Get the tasks in the repository.
     *
     * @return (std::vector<Task>) The tasks in the repository.
     */
    std::vector<Task> getTasks() const {
        std::vector<Task> tasks = readTasks();
        return tasks;
    }

    /*
     * Get the task with a specific id from the repository.
     *
     * @return Task The matching task.
     *
     * @raise (TaskMissing) If a task with that id does not exist.
     */
    Task getTaskById(int id) const {
        std::vector<Task> tasks = readTasks();
        for (Task t : tasks) {
            if (t.getId() == id) {
                return t;
            }
        }

        throw TaskMissing();
    }
    /*
     * Add a task to the repository.
     *
     * @param task (Task) The task to be added.
     *
     * @raise (TaskExists) If a task with that id already exists.
     */
    void addTask(const Task& task) const {
        std::vector<Task> tasks = readTasks();
        for (const Task& t : tasks) {
            if (t.getId() == task.getId()) {
                throw TaskExists();
            }
        }

        tasks.push_back(task);
        writeTasks(tasks);
    }

    /*
     * Update the state of a task.
     *
     * @param task (Task) The task to update.
     * @param state (std::string) The new state of the task.
     *
     * @return (bool) Whether the task has been successfully updated.
     */
    bool updateTaskState(Task& task, std::string state) const {
        std::vector<Task> tasks = readTasks();
        for (Task& t : tasks) {
            if (task.getId() == t.getId()) {
                task.setState(state);
                t.setState(state);
                writeTasks(tasks);
                return true;
            }
        }

        return false;
    }

private:
    std::vector<Task> readTasks() const {
        std::vector<Task> tasks;

        std::ifstream in(path);

        std::string line;
        std::string word;
        std::vector<std::string> words;
        while(getline(in, line)) {
            std::stringstream ss(line);
            words.clear();

            while(getline(ss, word, ',')) {
                words.push_back(word);
            }

            int id = stoi(words[0]);
            std::string description = words[1];
            std::string status = words[2];
            std::vector<std::string> programmers;

            for (size_t i = 3; i < words.size(); i++) {
                programmers.push_back(words[i]);
            }

            Task task{id, description, status, programmers};
            tasks.push_back(task);
        }

        return tasks;
    }

    void writeTasks(std::vector<Task> tasks) const {
        std::ofstream out(path);

        for (const Task& task : tasks) {
            out << task.getId() << ","
                << task.getDescription() << ","
                << task.getState() << ",";

            for (const std::string& programmer : task.getProgrammers()) {
                out << programmer << ",";
            }

            out << "\n";
        }
    }

    std::string path;
};

#endif // TASK_REPOSITORY_H
