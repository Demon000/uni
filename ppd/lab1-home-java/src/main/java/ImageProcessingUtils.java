public class ImageProcessingUtils {
    public static void averagePixels(Image source, Image target, int x, int y, int size) {
        int sum = 0;
        int count = 0;

        for (int i = y - (size - 1); i <= y; i++) {
            if (i < 0 || i >= source.getHeight()) {
                continue;
            }

            for (int j = x - (size - 1); j <= x; j++) {
                if (j < 0 || j >= source.getWidth()) {
                    continue;
                }

                sum += source.getPixel(j, i);
                count++;
            }
        }

        target.setPixel(x, y, sum / count);
    }
}
