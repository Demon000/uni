package utils;

import java.util.Arrays;
import java.util.stream.Collectors;

public class StringUtils {
    private static final String WORD_SEPARATOR = " ";

    public static String toTitleCase(String word) {
        if (word == null || word.isEmpty()) {
            return word;
        }

        return Character.toTitleCase(word.charAt(0)) + word.substring(1).toLowerCase();
    }

    public static String toTitleCaseText(String text) {
        if (text == null || text.isEmpty()) {
            return text;
        }

        return Arrays
                .stream(text.split(WORD_SEPARATOR))
                .map(StringUtils::toTitleCase)
                .collect(Collectors.joining(WORD_SEPARATOR));
    }
}
