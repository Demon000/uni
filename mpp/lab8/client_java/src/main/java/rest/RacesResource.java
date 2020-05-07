package rest;

import domain.Arbiter;
import domain.Race;

import javax.ws.rs.client.Entity;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.GenericType;
import javax.ws.rs.core.MediaType;
import java.util.List;

public class RacesResource {
    private final API api;

    public RacesResource(API api) {
        this.api = api;
    }

    public Race add(String name, Integer arbiterId) {
        WebTarget target = api.getTarget().path("/races");
        Race race = new Race(name, new Arbiter(arbiterId));
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .post(Entity.json(race), Race.class);
    }

    public Race findById(Integer id) {
        WebTarget target = api.getTarget().path("/races/" + id);
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .get(Race.class);
    }

    public List<Race> find() {
        WebTarget target = api.getTarget().path("/races");
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .get(new GenericType<>(){});
    }

    public Race update(Integer id, String name, Integer arbiterId) {
        WebTarget target = api.getTarget().path("/races/" + id);
        Race race = new Race(name, new Arbiter(arbiterId));
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .post(Entity.json(race), Race.class);
    }

    public Race delete(Integer id) {
        WebTarget target = api.getTarget().path("/races/" + id);
        return target
                .request(MediaType.APPLICATION_JSON_TYPE)
                .delete(Race.class);
    }
}
