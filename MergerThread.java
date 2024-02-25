public class MergerThread {
    private double[] firstHalf;
    private double[] secondHalf;
    private double[] mergedArray;

    public MergerThread(double[] firstHalf, double[] secondHalf) {
        this.firstHalf = firstHalf;
        this.secondHalf = secondHalf;
        this.mergedArray = new double[firstHalf.length + secondHalf.length];
    }

    public void run() {
        mergeArrays(firstHalf, secondHalf);
    }

    private void mergeArrays(double[] firstHalf, double[] secondHalf) {
        int i = 0, j = 0, k = 0;
        while (i < firstHalf.length && j < secondHalf.length) {
            if (firstHalf[i] < secondHalf[j]) {
                mergedArray[k++] = firstHalf[i++];
            } else {
                mergedArray[k++] = secondHalf[j++];
            }
        }
        while (i < firstHalf.length) {
            mergedArray[k++] = firstHalf[i++];
        }
        while (j < secondHalf.length) {
            mergedArray[k++] = secondHalf[j++];
        }
    }

    public double[] getMergedArray() {
        return mergedArray;
    }
}
