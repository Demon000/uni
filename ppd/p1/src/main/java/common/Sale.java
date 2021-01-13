package common;

import java.io.Serializable;
import java.util.ArrayList;

public class Sale implements Serializable {
    public ArrayList<Integer> soldSeatIds;
    public int showId;
    public int sum;
    public int id;

    public Sale(int id, int showId, int sum, ArrayList<Integer> soldSeatIds) {
        this.id = id;
        this.showId = showId;
        this.sum = sum;
        this.soldSeatIds = soldSeatIds;
    }

    @Override
    public String toString() {
        return "Sale{" +
                "soldSeatIds=" + soldSeatIds +
                ", showId=" + showId +
                ", sum=" + sum +
                ", id=" + id +
                '}';
    }
}
