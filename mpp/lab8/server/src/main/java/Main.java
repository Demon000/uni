import domain.Arbiter;
import domain.Race;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import repository.*;
import rest.RestApplication;
import utils.Configuration;
import repository.RepositoryUtils;

import java.util.List;

public class Main {
    private static final Configuration configuration = new Configuration(Main.class);
    private static IArbiterRepository arbiterRepository;
    private static SessionFactory sessionFactory;
    private static IRaceRepository raceRepository;
    private static Server server;

    public static void tryAddArbiter(Arbiter arbiter) {
        try {
            arbiterRepository.add(arbiter);
        } catch (RepositoryError e) {
            e.printStackTrace();
        }
    }

    public static void tryAddRace(Race race) {
        try {
            raceRepository.add(race);
        } catch (RepositoryError e) {
            e.printStackTrace();
        }
    }

    public static void printArbiters(List<Arbiter> arbiters) {
        arbiters.forEach(System.out::println);
        System.out.println();
    }

    public static void tryPrintAllArbiters() {
        try {
            List<Arbiter> arbiters = arbiterRepository.find();
            printArbiters(arbiters);
        } catch (RepositoryError e) {
            e.printStackTrace();
        }
    }

    public static void createHibernateSessionFactory() {
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure()
                .build();
        try {
            sessionFactory = new MetadataSources(registry)
                    .addAnnotatedClass(Arbiter.class)
                    .addAnnotatedClass(Race.class)
                    .buildMetadata()
                    .buildSessionFactory();
        } catch (Exception e) {
            StandardServiceRegistryBuilder.destroy(registry);
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createHibernateArbiterRepository() {
        arbiterRepository = new ArbiterHibernateRepository(sessionFactory);
        RepositoryUtils.setArbiterRepository(arbiterRepository);
    }

    public static void createHibernateRaceRepository() {
        raceRepository = new RaceHibernateRepository(sessionFactory);
        RepositoryUtils.setRaceRepository(raceRepository);
    }

    public static int SERVER_PORT = configuration.getIntegerValue("server_port", 8080);
    public static void createServer() {
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");

        server = new Server(SERVER_PORT);
        server.setHandler(context);

        ServletHolder jerseyServlet = context.addServlet(
                org.glassfish.jersey.servlet.ServletContainer.class, "/api/*");
        jerseyServlet.setInitOrder(0);

        jerseyServlet.setInitParameter(
                "javax.ws.rs.Application",
                RestApplication.class.getCanonicalName());
    }

    public static void startServer() {
        try {
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            server.destroy();
        }
    }

    public static void main(String[] args) {
        createHibernateSessionFactory();
        createHibernateArbiterRepository();
        createHibernateRaceRepository();
        createServer();

        Arbiter first = new Arbiter("Cosmin Tanislav", "passwordcosmin");
        tryAddArbiter(first);
        tryAddRace(new Race(first, "CYCLING"));

        Arbiter second = new Arbiter("Mihai Solcan", "passwordsolcan");
        tryAddArbiter(second);
        tryAddRace(new Race(second, "RUNNING"));

        Arbiter third = new Arbiter("Teodor Spiridon", "passwordrunning");
        tryAddArbiter(third);
        tryAddRace(new Race(third, "SWIMMING"));

        tryPrintAllArbiters();

        startServer();
    }
}
