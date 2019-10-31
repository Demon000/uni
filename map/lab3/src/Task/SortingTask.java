package Task;

import Utility.AbstractSorter;
import Utility.BubbleSort;
import Utility.QuickSort;
import Utility.SortingStrategy;

import java.util.Arrays;

public class SortingTask extends BaseTask {
    private int[] vector;
    private AbstractSorter sorter;

    public SortingTask(String id, String description, int[] vector, SortingStrategy sortingStrategy) {
        super(id, description);

        this.vector = vector;
        if (sortingStrategy == SortingStrategy.FIFO) {
            sorter = new BubbleSort();
        } else if (sortingStrategy == SortingStrategy.LIFO) {
            sorter = new QuickSort();
        }
    }

    @Override
    public void execute() {
        sorter.sort(vector);
        System.out.println(Arrays.toString(vector));
    }
}
