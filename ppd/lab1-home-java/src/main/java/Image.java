import java.io.*;
import java.util.Scanner;

public class Image {
    public Image(int width, int height) {
        this(width, height, width * height);
    }

    public Image(int width, int height, int size) {
        this(width, height, 0, size);
    }

    public Image(int width, int height, int start, int end) {
        resize(width, height, end - start);
        this.start = start;
        this.end = end;
    }

    public void resize(int width, int height, int size) {
        this.width = width;
        this.height = height;
        this.size = size;
        this.pixels = new int[size];
    }

    public int mapCoordinates(int x, int y) {
        return y * width + x;
    }

    public int mapCoordinatesX(int i) {
        return i % width;
    }

    public int mapCoordinatesY(int i) {
        return i / width;
    }

    private void checkAccess(int i) {
        if (i < start) {
            throw new ImageException("Accessing value before skip image data");
        }

        if (i >= end) {
            throw new ImageException("Accessing value after skip image data");
        }
    }

    public void setPixel(int i, int value) {
        checkAccess(i);
        pixels[i - start] = value;
    }

    public void setPixel(int x, int y, int value) {
        setPixel(mapCoordinates(x, y), value);
    }

    public int getPixel(int i) {
        checkAccess(i);
        return pixels[i - start];
    }

    public int getPixel(int x, int y) {
        return getPixel(mapCoordinates(x, y));
    }

    public int[] getPixels() {
        return pixels;
    }

    public int getStart() {
        return start;
    }

    public int getEnd() {
        return end;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getSize() {
        return width * height;
    }

    public int getRealSize() {
        return size;
    }

    public boolean isSkip() {
        return getSize() != getRealSize();
    }

    public static Image readFromFile(String path) throws IOException, ImageException {
        FileReader reader = new FileReader(path);
        Scanner scanner = new Scanner(reader);
        int width, height;

        if (!scanner.hasNextInt()) {
            throw new ImageException("Failed to read width");
        }
        width = scanner.nextInt();

        if (!scanner.hasNextInt()) {
            throw new ImageException("Failed to read height");
        }
        height = scanner.nextInt();

        Image image = new Image(width, height);

        for (int i = 0; i < width * height; i++) {
            if (!scanner.hasNextInt()) {
                throw new ImageException("Failed to read pixel");
            }

            int pixel = scanner.nextInt();
            image.setPixel(i, pixel);
        }

        scanner.close();
        reader.close();

        return image;
    }

    public static Image generateRandom(int width, int height) {
        Image image = new Image(width, height);

        for (int i = 0; i < width * height; i++) {
            image.setPixel(i, Utils.generateRandomInt(0, 256));
        }

        return image;
    }

    public void writeToFile(String path) throws IOException {
        PrintWriter writer = new PrintWriter(path);

        writer.println(width);
        writer.println(height);
        for (int i = 0; i < width * height; i++) {
            writer.println(getPixel(i));
        }

        writer.close();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append(String.format("Width: %d, height: %d\n", width, height));
        for (int i = 0; i < width * height; i++) {
            sb.append(getPixel(i));

            if (i % width == width - 1) {
                sb.append("\n");
            } else {
                sb.append(" ");
            }
        }

        return sb.toString();
    }

    protected int[] pixels;
    protected int width;
    protected int height;
    protected int size;
    protected int start;
    protected int end;
}
