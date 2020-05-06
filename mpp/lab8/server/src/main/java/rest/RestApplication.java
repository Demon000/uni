package rest;

import java.util.HashSet;
import java.util.Set;

public class RestApplication extends javax.ws.rs.core.Application {
    public Set<Class<?>> getClasses() {
        Set<Class<?>> s = new HashSet<>();
        s.add(API.class);
        s.add(ArbitersResource.class);
        s.add(RacesResource.class);
        return s;
    }
}
