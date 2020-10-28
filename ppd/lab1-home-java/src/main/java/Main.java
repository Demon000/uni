import java.io.IOException;
import java.util.concurrent.CountDownLatch;

interface IProcessing {
    void operation(Image image, int p, int size);
}

public class Main {
    public static final String INPUT_FILE_PATH = "date.txt";
    public static final int THREADS = 0;
    public static final int SEQUENTIAL = 1;

    public static void runThreads(Image image, int p, int size) {
        CountDownLatch latch = new CountDownLatch(p);
        CacheOutputImageProcessingThread[] threads = new CacheOutputImageProcessingThread[p];
        int n = image.getWidth() * image.getHeight();
        int chunk = n / p;
        int rest = n % p;
        int start;
        int end = 0;

        for (int i = 0; i < p; i++) {
            start = end;
            end = start + chunk;

            if (end > n) {
                end = n;
            }

            if (rest > 0) {
                end += 1;
                rest--;
            }

            threads[i] = new CacheOutputImageProcessingThread(image, latch, start, end, size);
            threads[i].start();
        }

        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void runSequential(Image image, int p, int size) {
        Image temp = new Image(image.getWidth(), image.getHeight());

        for (int i = 0; i < image.getHeight(); i++) {
            for (int j = 0; j < image.getWidth(); j++) {
                ImageProcessingUtils.averagePixels(image, temp, j, i, size);
            }
        }

        ImageUtils.copyPixels(temp, image);
    }

    public static void runWithParameters(int width, int height, int size, int type, int threads,
                                         int runs, boolean dump) {
        IProcessing processingFn;
        switch (type) {
            case THREADS:
                processingFn = Main::runThreads;
                break;
            case SEQUENTIAL:
                processingFn = Main::runSequential;
                break;
            default:
                System.out.println("Invalid processing type");
                return;
        }

        long averageDuration = 0;
        for (int i = 0; i < runs; i++) {
            Image image;
            try {
                image = Image.readFromFile(INPUT_FILE_PATH);
            } catch (ImageException | IOException e) {
                e.printStackTrace();
                return;
            }

            if (dump) {
                System.out.print("Before: ");
                System.out.println(image);
            }

            long startTime = System.nanoTime();
            processingFn.operation(image, threads, size);
            averageDuration += System.nanoTime() - startTime;

            if (dump) {
                System.out.print("After: ");
                System.out.println(image);
            }
        }

        averageDuration /= 1000000;
        averageDuration /= runs;

        System.out.printf("Average duration: %d\n", averageDuration);
    }

    // Width, height, kernel, processing type, number of threads
    static final int[][] parameters = {
            { 10, 10, 3, SEQUENTIAL, 0 },
            { 10, 10, 3, THREADS, 4 },

            { 1000, 1000, 5, SEQUENTIAL, 0 },
            { 1000, 1000, 5, THREADS, 2 },
            { 1000, 1000, 5, THREADS, 4 },
            { 1000, 1000, 5, THREADS, 8 },
            { 1000, 1000, 5, THREADS, 16 },

            { 10, 10000, 5, SEQUENTIAL, 0 },
            { 10, 10000, 5, THREADS, 2 },
            { 10, 10000, 5, THREADS, 4 },
            { 10, 10000, 5, THREADS, 8 },
            { 10, 10000, 5, THREADS, 16 },

            { 10000, 10, 5, SEQUENTIAL, 0 },
            { 10000, 10, 5, THREADS, 2 },
            { 10000, 10, 5, THREADS, 4 },
            { 10000, 10, 5, THREADS, 8 },
            { 10000, 10, 5, THREADS, 16 },
    };

    public static void main(String[] args) {
        boolean dump = false;
        int runs = 5;
        int lastWidth = 0;
        int lastHeight = 0;

        for (int[] parameter : parameters) {
            System.out.printf("Running N=%d, M=%d, n=m=%d", parameter[0], parameter[1], parameter[2]);

            if (parameter[3] == THREADS) {
                System.out.printf(", p=%d\n", parameter[4]);
            } else if (parameter[3] == SEQUENTIAL) {
                System.out.print(", p=sequential\n");
            }

            if (lastWidth != parameter[0] || lastHeight != parameter[1]) {
                lastWidth = parameter[0];
                lastHeight = parameter[1];

                Image generatedImage = Image.generateRandom(lastWidth, lastHeight);
                try {
                    generatedImage.writeToFile(INPUT_FILE_PATH);
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }
            }

            runWithParameters(parameter[0], parameter[1],
                    parameter[2], parameter[3], parameter[4], runs, dump);
        }
    }
}
