package Runner;

import Task.BaseTask;

abstract class AbstractTaskRunner implements ITaskRunner {
    ITaskRunner tr;

    AbstractTaskRunner(ITaskRunner tr) {
        this.tr = tr;
    }

    public void addTask(BaseTask task) {
        tr.addTask(task);
    }

    public boolean hasTask() {
        return tr.hasTask();
    }

    public void executeAll() {
        while (tr.hasTask()) {
            executeOneTask();
        }
    }
}
