package domain;

public class Room extends BaseEntity<Integer> {
    public Room(Integer number) {
        super(number);
    }

    public int getNumber() {
        return getId();
    }
}
