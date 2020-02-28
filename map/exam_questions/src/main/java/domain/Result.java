package domain;

public class Result {
    private final String name;
    private final float points;

    public Result(String name, Float points) {
        this.name = name;
        this.points = points;
    }

    public String getName() {
        return name;
    }

    public float getPoints() {
        return points;
    }
}
