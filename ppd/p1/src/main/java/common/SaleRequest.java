package common;

import java.io.Serializable;
import java.util.ArrayList;

public class SaleRequest implements Serializable {
    public int showId;
    public ArrayList<Integer> seatIds;

    public SaleRequest(int showId, ArrayList<Integer> seatIds) {
        this.showId = showId;
        this.seatIds = seatIds;
    }

    @Override
    public String toString() {
        return "SaleRequest{" +
                "showId=" + showId +
                ", seatIds=" + seatIds +
                '}';
    }
}
