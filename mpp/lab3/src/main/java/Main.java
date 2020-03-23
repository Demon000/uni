import domain.Arbiter;
import domain.Participant;
import domain.RaceType;
import org.apache.logging.log4j.LogManager;
import repository.DatabaseError;
import repository.DatabaseRepository;
import utils.ConfigManager;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

public class Main {
    public static void printParticipants(List<Participant> participants) {
        System.out.println();
        System.out.println("START PRINT PARTICIPANTS");
        participants.forEach(System.out::println);
        System.out.println("END PRINT PARTICIPANTS");
        System.out.println();
    }

    public static void printParticipant(Participant participant) {
        System.out.println("PARTICIPANT: " + participant);
        System.out.println();
    }

    public static void printArbiters(List<Arbiter> arbiters) {
        System.out.println();
        System.out.println("START PRINT ARBITERS");
        arbiters.forEach(System.out::println);
        System.out.println("END PRINT ARBITERS");
        System.out.println();
    }

    public static void printArbiter(Arbiter arbiter) {
        System.out.println("ARBITER: " + arbiter);
        System.out.println();
    }

    public static void main(String[] args) {
        ConfigManager configManager = new ConfigManager();

        Connection connection;
        try {
            connection = DriverManager.getConnection(configManager.getValue("database_url"));
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        try {
            DatabaseRepository<Participant> repository =
                    new DatabaseRepository<>(Participant.class, connection);
            Participant participant = new Participant("Christian Tatoiu");

            printParticipants(repository.find());

            repository.add(participant);
            printParticipants(repository.find());

            Participant found = repository.findById(new Participant("Christian Tatoiu"));
            printParticipant(found);

            repository.delete(participant);
            printParticipants(repository.find());
        } catch (DatabaseError databaseError) {
            databaseError.printStackTrace();
        }

        try {
            DatabaseRepository<Arbiter> repository =
                    new DatabaseRepository<>(Arbiter.class, connection);
            Arbiter arbiter = new Arbiter("Teodor Spiridon", RaceType.CYCLING.ordinal());

            printArbiters(repository.find());

            repository.add(arbiter);
            printArbiters(repository.find());

            Arbiter found = repository.findById(new Arbiter("Teodor Spiridon"));
            printArbiter(found);

            repository.delete(arbiter);
            printArbiters(repository.find());
        } catch (DatabaseError databaseError) {
            databaseError.printStackTrace();
        }
    }
}
