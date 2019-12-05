import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

class Grade {
    int value;

    public Grade(int value) {
        this.value = value;
    }

    public int getValue() { return value; }
}

public class Main {
    public static void main(String[] args) {
        List<Grade> grades = new ArrayList<>();
        grades.add(new Grade(5));
        grades.add(new Grade(5));
        grades.add(new Grade(7));
        grades.add(new Grade(3));
        grades.add(new Grade(3));

        Optional<Integer> result = grades.stream()
                .filter(grade -> grade.getValue() > 5)
                .map(Grade::getValue)
                .reduce(Integer::sum);

        System.out.println(result.get());
    }
}
