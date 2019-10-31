package Container;

import Task.BaseTask;

public class QueueContainer extends AbstractContainer {
    public QueueContainer() {
    }

    @Override
    public BaseTask remove() {
        if (isEmpty()) {
            return null;
        }

        return tasks[--size];
    }
}
