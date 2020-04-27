package utils;

import java.util.Set;

public class ThreadUtils {
    public static void printRunningThreads() {
        Thread printer = new Thread(() -> {
            while (true) {
                Set<Thread> threads = Thread.getAllStackTraces().keySet();
                int runningThreads = 0;
                for (Thread thread : threads) {
                    if (thread == Thread.currentThread()) {
                        continue;
                    }

                    if (thread.isAlive()) {
                        runningThreads += 1;
                    }

                    System.out.println(thread.getState() + " : " + thread.getName());
                    for (StackTraceElement trace: thread.getStackTrace()) {
                        System.out.println(trace);
                    }
                    System.out.println();
                }
                System.out.println("RUNNING THREADS: " + runningThreads);

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    return;
                }
            }
        });
        printer.start();
    }
}
