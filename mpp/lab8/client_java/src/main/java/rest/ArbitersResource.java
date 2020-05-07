package rest;

import domain.Arbiter;

import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.GenericType;
import javax.ws.rs.core.MediaType;
import java.util.List;

public class ArbitersResource {
    private final API api;

    public ArbitersResource(API api) {
        this.api = api;
    }

    public List<Arbiter> find() {
        WebTarget target = api.getTarget().path("/arbiters");
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .get(new GenericType<>() {
                });
    }
}
