public class SorterThread extends Thread {
    private double[] array;
    private double[] sortedArray;

    public SorterThread(double[] array) {
        this.array = array;
    }

    @Override
    public void run() {
        insertionSort(array);
        sortedArray = array;
    }

    private void insertionSort(double[] array) {
        int i;

        for (i = 1; i < array.length; i++) {
            double key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = key;
        }
    }

    public double[] getSortedArray() {
        return sortedArray;
    }
}
