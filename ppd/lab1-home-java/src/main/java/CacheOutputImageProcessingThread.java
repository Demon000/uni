import java.util.concurrent.CountDownLatch;

public class CacheOutputImageProcessingThread extends Thread {
    private final int size;
    private final Image image;
    private final Image local;
    private final int start;
    private final int end;
    private final CountDownLatch latch;

    public CacheOutputImageProcessingThread(Image image, CountDownLatch latch, int start, int end, int size) {
        this.local = new Image(image.getWidth(), image.getHeight(), start, end);
        this.image = image;
        this.latch = latch;
        this.start = start;
        this.end = end;
        this.size = size;
    }

    public void run() {
        for (int i = start; i < end; i++) {
            process(image.mapCoordinatesX(i), image.mapCoordinatesY(i));
        }

        latch.countDown();

        try {
            latch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
            return;
        }

        ImageUtils.copyPixels(local, image);
    }

    public void process(int x, int y) {
        ImageProcessingUtils.averagePixels(image, local, x, y, size);
    }
}
