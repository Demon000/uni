package Utility;

public class QuickSort extends AbstractSorter {
    private int partition(int[] vector, int low, int high) {
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (vector[j] < vector[high]) {
                swap(vector, ++i, j);
            }
        }

        swap(vector, ++i, high);

        return i;
    }

    private void sort_r(int[] vector, int low, int high) {
        if (low < high) {
            int pi = partition(vector, low, high);
            sort_r(vector, low, pi - 1);
            sort_r(vector, pi + 1, high);
        }
    }

    @Override
    public void sort(int[] vector) {
        sort_r(vector, 0, vector.length - 1);
    }
}
