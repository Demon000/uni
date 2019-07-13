#include <cassert>
#include <iostream>

#include "entities/Task.h"
#include "repositories/TaskRepository.h"
#include "services/TaskService.h"

void test_task() {
    std::vector<std::string> programmers{"One name", "Another Name"};
    Task first{1, "First task", "open", programmers};

    assert(first.getId() == 1);
    assert(first.getDescription() == "First task");
    assert(first.getState() == "open");
    assert(first.getNumberOfProgrammers() == 2);
    assert(first.isProgrammer("One") == true);
    assert(first.isProgrammer("Not one") == false);

    first.setState("closed");
    assert(first.getState() == "closed");
}

void test_repository() {
    TaskRepository repository{"test_tasks_repository.csv"};
    std::vector<Task> tasks;

    Task first{1, "First task", "open", {"One name", "Another Name"}};
    repository.addTask(first);

    Task second{2, "Second task", "closed", {"Last Name"}};
    repository.addTask(second);

    tasks = repository.getTasks();
    assert(tasks[0].getId() == 1);
    assert(tasks[0].getDescription() == "First task");
    assert(tasks[0].getState() == "open");
    assert(tasks[0].getNumberOfProgrammers() == 2);

    assert(tasks[1].getId() == 2);
    assert(tasks[1].getDescription() == "Second task");
    assert(tasks[1].getState() == "closed");
    assert(tasks[1].getNumberOfProgrammers() == 1);

    Task found = repository.getTaskById(1);
    assert(found.getId() == 1);
    assert(found.getDescription() == "First task");
    assert(found.getState() == "open");
    assert(found.getNumberOfProgrammers() == 2);

    try {
        repository.getTaskById(3);
        assert(false);
    } catch (TaskMissing&) {
        assert(true);
    }

    repository.updateTaskState(first, "closed");
    tasks = repository.getTasks();
    assert(tasks[0].getState() == "closed");

    try {
        repository.addTask(first);
        assert(false);
    } catch (TaskExists&) {
        assert(true);
    }
}

void test_service() {
    TaskRepository repository{"test_tasks_service.csv"};
    TaskValidator validator;
    TaskService service{repository, validator};
    std::vector<Task> tasks;

    service.addTask(1, "First task", "open", {"One name", "Another Name"});
    service.addTask(2, "Second task", "closed", {"Last Name"});
    service.addTask(3, "Third task", "inprogress", {"What name"});

    tasks = service.getTasks();
    assert(tasks[0].getId() == 2);
    assert(tasks[1].getId() == 3);
    assert(tasks[2].getId() == 1);

    tasks = service.getFilteredTasks("One");
    assert(tasks[0].getId() == 1);
}

int main() {
    test_task();
    test_repository();
    test_service();

    return 0;
}
