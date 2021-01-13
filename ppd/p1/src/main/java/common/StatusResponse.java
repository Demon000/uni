package common;

import java.io.Serializable;

public class StatusResponse implements Serializable {
    public Boolean status;

    public StatusResponse(Boolean status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "StatusResponse{" +
                "status=" + status +
                '}';
    }
}
