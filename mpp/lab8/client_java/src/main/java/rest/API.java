package rest;

import org.glassfish.jersey.client.ClientConfig;
import org.glassfish.jersey.logging.LoggingFeature;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;

public class API {
    private final WebTarget target;

    public API(String host, int port) {
        String path = String.format("%s:%d/api", host, port);
        ClientConfig clientConfig = new ClientConfig();
        clientConfig.property(LoggingFeature.LOGGING_FEATURE_VERBOSITY, LoggingFeature.Verbosity.PAYLOAD_ANY);
        Client client = ClientBuilder.newBuilder().withConfig(clientConfig).build();
        this.target = client.target(path);
    }

    public WebTarget getTarget() {
        return target;
    }
}
