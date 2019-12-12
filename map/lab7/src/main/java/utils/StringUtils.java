package utils;

public class StringUtils {
    public static boolean matchesAny(String input, String ...what) {
        String lowerInput = input.toLowerCase();
        for (String w : what) {
            String lower = w.toLowerCase();
            if (lower.contains(lowerInput)) {
                return true;
            }
        }

        return false;
    }
}
