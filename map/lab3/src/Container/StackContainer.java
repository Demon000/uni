package Container;

import Task.BaseTask;

public class StackContainer extends AbstractContainer {
    public StackContainer() {
    }

    @Override
    public BaseTask remove() {
        if (isEmpty()) {
            return null;
        }

        BaseTask task = tasks[0];
        System.arraycopy(tasks, 1, tasks, 0, tasks.length - 1);
        size--;

        return task;
    }
}
