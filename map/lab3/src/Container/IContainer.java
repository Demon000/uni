package Container;

import Task.BaseTask;

public interface IContainer {
    BaseTask remove();
    void add(BaseTask task);
    int size();
    boolean isEmpty();
}
