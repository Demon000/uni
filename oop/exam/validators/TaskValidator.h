#include <string>

#include "../entities/Task.h"

#ifndef TASK_VALIDATOR_H
#define TASK_VALIDATOR_H

class TaskValidator {
public:
    void validate(const Task& task) {
        validateDescription(task.getDescription());
        validateState(task.getState());
        validateNumberOfProgrammers(task.getNumberOfProgrammers());
    }

    void validateDescription(std::string description) {
        if (description == "") {
            throw TaskDescriptionMissing();
        }
    }

    void validateState(std::string state) {
        if (state != "open" &&
                state != "closed" &&
                state != "inprogress") {
            throw TaskStateWrong();
        }
    }

    void validateNumberOfProgrammers(int noProgrammers) {
        if (noProgrammers < 1 ||
                noProgrammers > 4) {
            throw TaskProgrammersNumberWrong();
        }
    }
};

#endif // TASK_VALIDATOR_H
