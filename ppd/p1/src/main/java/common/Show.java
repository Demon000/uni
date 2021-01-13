package common;

import java.io.Serializable;
import java.util.ArrayList;

public class Show implements Serializable {
    public String title;
    public int id;
    public int price;
    public int noSeats;
    public int sum = 0;
    public ArrayList<Integer> soldSeatIds = new ArrayList<>();

    public Show(int id, String title, int price, int noSeats) {
        this.title = title;
        this.id = id;
        this.price = price;
        this.noSeats = noSeats;
    }

    @Override
    public String toString() {
        return "Show{" +
                "title='" + title + '\'' +
                ", id=" + id +
                ", price=" + price +
                ", noSeats=" + noSeats +
                ", sum=" + sum +
                ", soldSeatIds=" + soldSeatIds +
                '}';
    }
}
