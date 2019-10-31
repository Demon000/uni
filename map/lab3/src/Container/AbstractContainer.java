package Container;

import Task.BaseTask;

public abstract class AbstractContainer implements IContainer {
    BaseTask[] tasks;
    int size;

    AbstractContainer() {
        tasks = new BaseTask[20];
        size = 0;
    }

    void resize() {
        BaseTask[] newTasks = new BaseTask[tasks.length * 2];
        System.arraycopy(tasks, 0, newTasks, 0, tasks.length);
        tasks = newTasks;
    }

    @Override
    public void add(BaseTask task) {
        if (size + 1 == tasks.length) {
            resize();
        }

        tasks[size++] = task;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }
}
