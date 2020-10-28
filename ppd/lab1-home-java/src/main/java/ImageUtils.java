public class ImageUtils {
    public static void copyPixels(Image source, Image target) {
        if (source.getSize() != target.getSize()) {
            throw new ImageException("Cannot copy pixels when sizes don't match");
        }

        if (source.isSkip() && target.isSkip()) {
            copyPixels(source, 0, target, 0, source.getRealSize());
        } else if (source.isSkip() && !target.isSkip()) {
            copyPixels(source, 0, target, source.getStart(), source.getRealSize());
        } else if (!source.isSkip() && target.isSkip()) {
            copyPixels(source, target.getStart(), target, 0, target.getRealSize());
        } else {
            copyPixels(source, 0, target, 0, source.getRealSize());
        }
    }

    public static void copyPixels(Image source, int sourceStart, Image target, int targetStart, int length) {
        System.arraycopy(source.getPixels(), sourceStart, target.getPixels(), targetStart, length);
    }
}
