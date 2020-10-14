import java.util.Random;

public class Main {
    public static class Job extends Thread {
        private final int start;
        private final int end;
        private final int[] a;
        private final int[] b;
        private final int[] c;

        public Job(int start, int end, int[] a, int[] b, int[] c) {
            super();

//            System.out.println(start + " " + end);

            this.start = start;
            this.end = end;
            this.a = a;
            this.b = b;
            this.c = c;
        }

        public void run() {
//            System.out.println(currentThread().getName());

            for (int i = start; i < end; i++) {
                c[i] = a[i] + b[i];
            }
        }
    }

    public static void runThreads(int n, int p, int[] a, int[] b, int[] c) {
        int chunk = n / p;
        int rest = n % p;
        int start;
        int end = 0;
        Job[] threads = new Job[p];

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

            threads[i] = new Job(start, end, a, b, c);
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

    public static void runSequential(int n, int[] a, int[] b, int[] c) {
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }

    public static void main(String[] args) {
        Random random = new Random();
        int n = 1_000_000_00;
        int p = 3;

        int[] a = new int[n];
        int[] b = new int[n];
        int[] c = new int[n];
        int[] d = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = random.nextInt(6);
            b[i] = random.nextInt(6);
        }

        long startTime;
        long duration;

        startTime = System.nanoTime();
        runSequential(n, a, b, c);
        duration = System.nanoTime() - startTime;

        System.out.println("runSequential: " + duration / 1_000);

        startTime = System.nanoTime();
        runThreads(n, p, a, b, d);
        duration = System.nanoTime() - startTime;

        System.out.println("runThreads: " + duration / 1_000);

//        System.out.println(Arrays.toString(a));
//        System.out.println(Arrays.toString(b));
//        System.out.println(Arrays.toString(c));
//        System.out.println(Arrays.toString(d));
    }
}
