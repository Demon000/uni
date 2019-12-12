package utils;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class CollectionUtils {
    public static <E> Stream<E> streamFromIterable(Iterable<E> iterable) {
        return StreamSupport.stream(iterable.spliterator(), false);
    }

    public static <E> List<E> listFromIterable(Iterable<E> iterable) {
        return streamFromIterable(iterable).collect(Collectors.toList());
    }
}
