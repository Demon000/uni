package Utility;

public abstract class AbstractSorter {
    public abstract void sort(int[] v);

    void swap(int[] v, int i, int j) {
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}
