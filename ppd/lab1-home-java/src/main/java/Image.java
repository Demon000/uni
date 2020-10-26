import java.io.*;
import java.util.Scanner;

public class Image {
    int[] pixels;
    int width;
    int height;

    public Image() {}

    public Image(int width, int height) {
        resize(width, height, width * height);
    }

    public Image(int width, int height, int size) {
        resize(width, height, size);
    }

    public void resize(int width, int height) {
        resize(width, height, width * height);
    }

    public void resize(int width, int height, int size) {
        this.width = width;
        this.height = height;
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

    public void setPixel(int i, int value) {
        pixels[i] = value;
    }

    public void setPixel(int x, int y, int value) {
        setPixel(mapCoordinates(x, y), value);
    }

    public int getPixel(int i) {
        return pixels[i];
    }

    public int getPixel(int x, int y) {
        return pixels[mapCoordinates(x, y)];
    }

    public int[] getPixels() {
        return pixels;
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
}
