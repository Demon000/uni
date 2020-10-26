public abstract class ImageProcessingThread extends Thread {
    public Image source;
    public Image target;
    public final int start;
    public final int end;

    public ImageProcessingThread(Image source, Image target, int start, int end) {
        this.source = source;
        this.target = target;
        this.start = start;
        this.end = end;
    }

    public abstract void process(int x, int y);

    public void run() {
//        System.out.printf("Starting image processing thread with start: %d, end: %d%n", start, end);
        for (int i = start; i < end; i++) {
            process(source.mapCoordinatesX(i), source.mapCoordinatesY(i));
        }
    }
}
