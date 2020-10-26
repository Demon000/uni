public class AverageImageProcessingThread extends ImageProcessingThread {
    private int size;

    public AverageImageProcessingThread(Image source, Image target, int start, int end, int size) {
        super(source, target, start, end);
        this.size = size;
    }

    @Override
    public void process(int x, int y) {
        ImageProcessingUtils.averagePixels(source, target, x, y, size);
    }
}
