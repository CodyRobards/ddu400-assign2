public class prog_j {
    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]); // Array size from command line
        double[] array = new double[N];
        generateRandomArray(array);

        // Two-thread sort
        long startTime = System.nanoTime();
        // Divide array for two-thread sorting
        double[] firstHalf = new double[N / 2];
        double[] secondHalf = new double[N / 2];
        System.arraycopy(array, 0, firstHalf, 0, N / 2);
        System.arraycopy(array, N / 2, secondHalf, 0, N / 2);

        SorterThread sortThread1 = new SorterThread(firstHalf);
        SorterThread sortThread2 = new SorterThread(secondHalf);
        sortThread1.start();
        sortThread2.start();
        try {
            sortThread1.join();
            sortThread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        MergerThread mergeThread = new MergerThread(sortThread1.getSortedArray(), sortThread2.getSortedArray());
        mergeThread.run(); // Merging in the main thread
        long endTime = System.nanoTime();
        System.out.println("Sorting is done in " + (endTime - startTime) / 1e6 + "ms when two threads are used");

        // Single-thread sort
        startTime = System.nanoTime();
        SorterThread singleSortThread = new SorterThread(array.clone());
        singleSortThread.run(); // Running in the main thread for single-threaded sort
        endTime = System.nanoTime();
        System.out.println("Sorting is done in " + (endTime - startTime) / 1e6 + "ms when one thread is used");
    }

    private static void generateRandomArray(double[] array) {
        int i;

        for (i = 0; i < array.length; i++) {
            array[i] = Math.random() * 1000;
        }
    }
}
