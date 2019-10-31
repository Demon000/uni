package Runner;

import Task.BaseTask;

public interface ITaskRunner {
    void executeOneTask();

    void executeAll();

    void addTask(BaseTask task);

    boolean hasTask();
}
