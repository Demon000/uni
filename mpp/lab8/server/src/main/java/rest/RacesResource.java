package rest;

import domain.Arbiter;
import domain.Race;
import repository.IArbiterRepository;
import repository.IRaceRepository;
import repository.RepositoryError;
import repository.RepositoryUtils;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.List;

@Path("/races")
public class RacesResource {
    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response add(Race.PostDocument document) {
        IArbiterRepository arbiterRepository = RepositoryUtils.getArbiterRepository();
        IRaceRepository raceRepository = RepositoryUtils.getRaceRepository();

        Arbiter arbiter;
        try {
            arbiter = arbiterRepository.findById(document.getArbiter().getId());
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .entity(e.getMessage())
                    .build();
        }

        Race race = new Race(arbiter, document.getName());
        try {
            raceRepository.add(race);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.INTERNAL_SERVER_ERROR)
                    .entity(e.getMessage())
                    .build();
        }

        return Response
                .ok()
                .entity(race)
                .build();
    }

    @GET
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response findById(@PathParam("id") int id) {
        IRaceRepository raceRepository = RepositoryUtils.getRaceRepository();
        Race race;

        try {
            race = raceRepository.findById(id);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .entity(e.getMessage())
                    .build();
        }

        if (race == null) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .build();
        }

        return Response
                .ok()
                .entity(race)
                .build();
    }

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response find() {
        IRaceRepository raceRepository = RepositoryUtils.getRaceRepository();
        List<Race> races;

        try {
            races = raceRepository.find();
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.INTERNAL_SERVER_ERROR)
                    .entity(e.getMessage())
                    .build();
        }

        return Response
                .ok()
                .entity(races)
                .build();
    }

    @POST
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response update(@PathParam("id") int id, Race.PostDocument document) {
        IArbiterRepository arbiterRepository = RepositoryUtils.getArbiterRepository();
        IRaceRepository raceRepository = RepositoryUtils.getRaceRepository();
        Race race;

        try {
            race = raceRepository.findById(id);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .entity(e.getMessage())
                    .build();
        }

        if (race == null) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .build();
        }

        if (document.getArbiter().getId() != null &&
                !document.getArbiter().getId().equals(race.getArbiter().getId())) {
            Arbiter arbiter;
            try {
                arbiter = arbiterRepository.findById(document.getArbiter().getId());
            } catch (RepositoryError e) {
                return Response
                        .status(Response.Status.NOT_FOUND)
                        .entity(e.getMessage())
                        .build();
            }

            race.setArbiter(arbiter);
        }

        if (document.getName() != null &&
                !document.getName().equals(race.getName())) {
            race.setName(document.getName());
        }

        try {
            raceRepository.update(race);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.INTERNAL_SERVER_ERROR)
                    .entity(e.getDocument())
                    .build();
        }

        return Response
                .ok()
                .entity(race)
                .build();
    }

    @DELETE
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response delete(@PathParam("id") int id) {
        IRaceRepository raceRepository = RepositoryUtils.getRaceRepository();
        Race race;

        try {
            race = raceRepository.findById(id);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .entity(e.getDocument())
                    .build();
        }

        if (race == null) {
            return Response
                    .status(Response.Status.NOT_FOUND)
                    .build();
        }

        try {
            raceRepository.delete(race);
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.INTERNAL_SERVER_ERROR)
                    .entity(e.getDocument())
                    .build();
        }

        return Response
                .ok()
                .entity(race)
                .build();
    }
}
