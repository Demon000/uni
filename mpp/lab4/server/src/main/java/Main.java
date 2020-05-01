import domain.Arbiter;
import domain.Participant;
import domain.Score;
import domain.ScoreType;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import repository.*;
import server.IServer;
import server.ObjectServer;
import server.RemoteServer;
import service.Service;
import utils.Configuration;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

public class Main {
    private static final Configuration configuration = new Configuration(Main.class);
    private static Connection connection;
    private static IParticipantRepository participantRepository;
    private static IArbiterRepository arbiterRepository;
    private static IScoreRepository scoreRepository;
    private static Service service;
    private static IServer server;
    private static SessionFactory sessionFactory;

    public static void tryAddParticipant(IParticipantRepository repository, Participant participant) {
        try {
            repository.add(participant);
        } catch (RepositoryError ignored) {
        }
    }

    public static void tryAddArbiter(IArbiterRepository repository, Arbiter arbiter) {
        try {
            repository.add(arbiter);
        } catch (RepositoryError ignored) {
        }
    }

    public static void trySetScore(IScoreRepository repository, int participantId, ScoreType type, int score) {
        try {
            repository.setScore(participantId, type, score);
        } catch (RepositoryError ignored) {
        }
    }

    public static void tryPrintArbiterByNameAndPassword(IArbiterRepository repository, String name, String password) {
        try {
            Arbiter arbiter = repository.findByNameAndPassword("Cosmin Tanislav", "passwordcosmin");
            System.out.println(arbiter);
        } catch (RepositoryError ignored) {
        }
    }

    public static void tryPrintTotalScoreSortedByName(IScoreRepository repository) {
        try {
            List<Score> scores = repository.findScoresSortedByName();
            System.out.println("Total scores sorted by name");
            scores.forEach(System.out::println);
            System.out.println();
        } catch (RepositoryError ignored) {
        }
    }

    public static void tryPrintScoresForTypeSortedDescending(IScoreRepository repository, ScoreType type) {
        try {
            List<Score> scores = repository.findScoresForTypeSortedDescending(type);
            System.out.println(String.format("Scores for %s sorted descending", type.toString().toLowerCase()));
            scores.forEach(System.out::println);
            System.out.println();
        } catch (RepositoryError ignored) {
        }
    }

    public static void createConnection() {
        try {
            connection = DriverManager.getConnection(configuration.getValue("database_url"));
        } catch (SQLException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void destroyConnection() {
        try {
            connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createHibernateSessionFactory() {
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure()
                .build();
        try {
            sessionFactory = new MetadataSources(registry)
                    .addAnnotatedClass(Arbiter.class)
                    .buildMetadata()
                    .buildSessionFactory();
        } catch (Exception e) {
            StandardServiceRegistryBuilder.destroy(registry);
            System.exit(-1);
        }
    }

    public static void createParticipantRepository() {
        try {
            participantRepository = new ParticipantRepository(connection);
        } catch (RepositoryError e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createArbiterRepository() {
        try {
            arbiterRepository = new ArbiterRepository(connection);
        } catch (RepositoryError e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createHibernateArbiterRepository() {
        arbiterRepository = new ArbiterHibernateRepository(sessionFactory);
    }

    public static void createScoreRepository() {
        try {
            scoreRepository = new ScoreRepository(connection);
        } catch (RepositoryError e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createService() {
        service = new Service(participantRepository, arbiterRepository, scoreRepository);
    }

    public static void createObjectServer() {
        server = new ObjectServer();
    }

    public static void createRemoteServer() {
        server = new RemoteServer();
    }

    public static void startServer() {
        try {
            server.start(service, configuration.getIntegerValue("server_port", 0));
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        createConnection();
        createHibernateSessionFactory();
        createParticipantRepository();
//        createArbiterRepository();
        createHibernateArbiterRepository();
        createScoreRepository();
        createService();
        createRemoteServer();

        tryAddParticipant(participantRepository, new Participant("Christian Tatoiu"));
        tryAddParticipant(participantRepository, new Participant("Radu Stefanescu"));
        tryAddParticipant(participantRepository, new Participant("Nicu Serte"));
        tryAddParticipant(participantRepository, new Participant("Alexandra Suciu"));
        tryAddParticipant(participantRepository, new Participant("Silvia Suciu"));
        tryAddParticipant(participantRepository, new Participant("Adrian Sopterean"));

        tryAddArbiter(arbiterRepository, new Arbiter("Cosmin Tanislav", "passwordcosmin", ScoreType.CYCLING));
        tryAddArbiter(arbiterRepository, new Arbiter("Mihai Solcan", "passwordsolcan", ScoreType.RUNNING));
        tryAddArbiter(arbiterRepository, new Arbiter("Teodor Spiridon", "passwordrunning", ScoreType.SWIMMING));
//        tryPrintArbiterByNameAndPassword(arbiterRepository, "Cosmin Tanislav", "passwordcosmin");

        trySetScore(scoreRepository, 1, ScoreType.CYCLING, 20);
        trySetScore(scoreRepository, 1, ScoreType.RUNNING, 20);
        trySetScore(scoreRepository, 1, ScoreType.SWIMMING, 10);
        trySetScore(scoreRepository, 2, ScoreType.CYCLING, 10);
        trySetScore(scoreRepository, 2, ScoreType.RUNNING, 10);
        trySetScore(scoreRepository, 2, ScoreType.SWIMMING, 10);
        trySetScore(scoreRepository, 3, ScoreType.CYCLING, 10);
        trySetScore(scoreRepository, 3, ScoreType.RUNNING, 5);
        trySetScore(scoreRepository, 3, ScoreType.SWIMMING, 5);
//        tryPrintTotalScoreSortedByName(scoreRepository);
//        tryPrintScoresForTypeSortedDescending(scoreRepository, ScoreType.CYCLING);
//        tryPrintScoresForTypeSortedDescending(scoreRepository, ScoreType.RUNNING);
//        tryPrintScoresForTypeSortedDescending(scoreRepository, ScoreType.SWIMMING);

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                server.stop();
                destroyConnection();
            } catch (IOException ignored) {
            }
        }));

        startServer();
    }
}
