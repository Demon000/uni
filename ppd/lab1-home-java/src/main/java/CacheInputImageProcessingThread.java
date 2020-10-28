import java.util.concurrent.CountDownLatch;

public class CacheInputImageProcessingThread extends Thread {
    private final int size;
    private final Image image;
    private final Image local;
    private final int start;
    private final int end;
    private final CountDownLatch latch;

    public CacheInputImageProcessingThread(Image image, CountDownLatch latch, int start, int end, int size) {
        int dataStart = Math.max(start - (size - 1) * image.width - (size - 1), 0);
        this.local = new Image(image.width, image.height, dataStart, end);
        this.image = image;
        this.latch = latch;
        this.start = start;
        this.end = end;
        this.size = size;
    }

    public void run() {
        ImageUtils.copyPixels(image, local);

        latch.countDown();

        try {
            latch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
            return;
        }

        for (int i = start; i < end; i++) {
            process(image.mapCoordinatesX(i), image.mapCoordinatesY(i));
        }
    }

    public void process(int x, int y) {
        ImageProcessingUtils.averagePixels(local, image, x, y, size);
    }
}
