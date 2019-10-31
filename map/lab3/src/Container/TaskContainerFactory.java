package Container;

import Utility.SortingStrategy;

public class TaskContainerFactory implements IContainerFactory {
    private static TaskContainerFactory instance;

    private TaskContainerFactory() {}

    public static TaskContainerFactory getInstance() {
        if (instance == null) {
            instance = new TaskContainerFactory();
        }

        return instance;
    }

    @Override
    public IContainer createContainer(SortingStrategy sortingStrategy) {
        if (sortingStrategy == SortingStrategy.FIFO) {
            return new StackContainer();
        } else if (sortingStrategy == SortingStrategy.LIFO) {
            return new QueueContainer();
        }

        return null;
    }
}
