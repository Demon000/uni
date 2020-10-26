import java.util.Arrays;

public class SkipImage extends Image {
    SkipImage(int start, int end, Image sourceImage) {
        super(sourceImage.width, sourceImage.height, end - start);
        this.start = start;
        this.end = end;
    }

    public void setPixel(int i, int value) {
        super.setPixel(i - start, value);
    }

    public int getPixel(int i) {
        return super.getPixel(i - start);
    }

    public int getStart() {
        return start;
    }

    public int getEnd() {
        return end;
    }

    private final int start;
    private final int end;
}
