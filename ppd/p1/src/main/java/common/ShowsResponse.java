package common;

import java.io.Serializable;
import java.util.ArrayList;

public class ShowsResponse implements Serializable {
    public ArrayList<Show> shows;

    public ShowsResponse(ArrayList<Show> shows) {
        this.shows = shows;
    }

    @Override
    public String toString() {
        return "ShowsResponse{" +
                "shows=" + shows +
                '}';
    }
}
