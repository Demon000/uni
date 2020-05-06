package rest;

import domain.Arbiter;
import repository.IArbiterRepository;
import repository.RepositoryError;
import utils.RepositoryUtils;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.List;

@Path("/arbiters")
public class ArbitersResource {
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response find() {
        IArbiterRepository repository = RepositoryUtils.getArbiterRepository();
        List<Arbiter> arbiters;

        try {
            arbiters = repository.find();
        } catch (RepositoryError e) {
            return Response
                    .status(Response.Status.INTERNAL_SERVER_ERROR)
                    .entity(e.getDocument())
                    .build();
        }

        return Response
                .ok()
                .entity(arbiters)
                .build();
    }
}
