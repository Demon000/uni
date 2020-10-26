import java.io.IOException;

interface IProcessing {
    void operation(Image source, Image target, int p, int size);
}

public class Main {
    public static final String INPUT_FILE_PATH = "date.txt";
    public static final int THREADS = 0;
    public static final int SEQUENTIAL = 1;

    public static void runThreads(Image source, Image target, int p, int size) {
        AverageImageProcessingThread[] threads = new AverageImageProcessingThread[p];
        int n = source.width * source.height;
        int chunk = n / p;
        int rest = n % p;
        int start;
        int end = 0;

        target.resize(source.width, source.height);

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

            threads[i] = new AverageImageProcessingThread(source, target, start, end, size);
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

    public static void runSequential(Image source, Image target, int p, int size) {
        target.resize(source.width, source.height);
        for (int i = 0; i < source.height; i++) {
            for (int j = 0; j < source.width; j++) {
                ImageProcessingUtils.averagePixels(source, target, j, i, size);
            }
        }
    }

    public static void runWithParameters(int width, int height, int size, int type, int threads, int runs) {
        Image generatedImage = Image.generateRandom(width, height);
        try {
            generatedImage.writeToFile(INPUT_FILE_PATH);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        Image sourceImage;
        try {
            sourceImage = Image.readFromFile(INPUT_FILE_PATH);
        } catch (ImageException | IOException e) {
            e.printStackTrace();
            return;
        }

        Image targetImage = new Image();
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


        long startTime = System.nanoTime();
        for (int i = 0; i < runs; i++) {
            processingFn.operation(sourceImage, targetImage, threads, size);
        }
        long averageDuration = System.nanoTime() - startTime;

        averageDuration /= 1000000;
        averageDuration /= runs;

        System.out.printf("Average duration: %d\n", averageDuration);
    }

    public static void main(String[] args) {
        int[][] parameters = {
                { 10, 10, 3, THREADS, 4 },
                { 10, 10, 3, SEQUENTIAL, 0 },

                { 1000, 1000, 5, THREADS, 2 },
                { 1000, 1000, 5, THREADS, 4 },
                { 1000, 1000, 5, THREADS, 8 },
                { 1000, 1000, 5, THREADS, 16 },
                { 1000, 1000, 5, SEQUENTIAL, 0 },

                { 10, 10000, 5, THREADS, 2 },
                { 10, 10000, 5, THREADS, 4 },
                { 10, 10000, 5, THREADS, 8 },
                { 10, 10000, 5, THREADS, 16 },
                { 10, 10000, 5, SEQUENTIAL, 0 },

                { 10000, 10, 5, THREADS, 2 },
                { 10000, 10, 5, THREADS, 4 },
                { 10000, 10, 5, THREADS, 8 },
                { 10000, 10, 5, THREADS, 16 },
                { 10000, 10, 5, SEQUENTIAL, 0 },
        };
        int runs = 5;

        for (int[] parameter : parameters) {
            System.out.printf("Running N=%d, M=%d, n=m=%d", parameter[0], parameter[1], parameter[2]);

            if (parameter[3] == THREADS) {
                System.out.printf(", p=%d\n", parameter[4]);
            } else if (parameter[3] == SEQUENTIAL) {
                System.out.print(", p=sequential\n");
            }

            runWithParameters(parameter[0], parameter[1],
                    parameter[2], parameter[3], parameter[4], runs);
        }
    }
}
