package Runner;

import Task.BaseTask;
import Container.IContainer;
import Container.TaskContainerFactory;
import Utility.SortingStrategy;

public class StrategyTaskRunner implements ITaskRunner {
    private IContainer container;

    public StrategyTaskRunner(SortingStrategy sortingStrategy) {
        TaskContainerFactory tc = TaskContainerFactory.getInstance();
        container = tc.createContainer(sortingStrategy);
    }

    @Override
    public void executeOneTask() {
        if (!hasTask()) {
            return;
        }

        container.remove().execute();
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(BaseTask task) {
        container.add(task);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
