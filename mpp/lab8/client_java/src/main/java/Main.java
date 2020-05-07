import domain.Arbiter;
import domain.Race;
import rest.API;
import rest.ArbitersResource;
import rest.RacesResource;
import utils.Configuration;

import java.util.List;

public class Main {
    private static final Configuration configuration = new Configuration(Main.class);
    private static API api;
    private static ArbitersResource arbitersResource;
    private static RacesResource racesResource;

    public static void printArbiters(List<Arbiter> arbiters) {
        arbiters.forEach(System.out::println);
        System.out.println();
    }

    public static void tryPrintAllArbiters() {
        try {
            List<Arbiter> arbiters = arbitersResource.find();
            printArbiters(arbiters);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Race tryAddRace(String name, Integer arbiterId) {
        try {
            return racesResource.add(name, arbiterId);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Race tryFindRaceById(Integer id) {
        try {
            return racesResource.findById(id);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Race tryUpdateRace(Integer id, String name, Integer arbiterId) {
        try {
            return racesResource.update(id, name, arbiterId);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Race tryDeleteRace(Integer id) {
        try {
            return racesResource.delete(id);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void printRaces(List<Race> races) {
        races.forEach(System.out::println);
        System.out.println();
    }

    public static void tryPrintAllRaces() {
        try {
            List<Race> races = racesResource.find();
            printRaces(races);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        api = new API(configuration.getValue("server_host"),
                configuration.getIntegerValue("server_port", 8080));
        arbitersResource = new ArbitersResource(api);
        racesResource = new RacesResource(api);

        System.out.println("All arbiters");
        tryPrintAllArbiters();

        System.out.println("All races");
        tryPrintAllRaces();

        Race race;

        race = tryAddRace("FANCY_CYCLING", 1);
        if (race == null) {
            System.out.println("Failed to add race");
            System.exit(-1);
        }
        System.out.println("Added: " + race);

        System.out.println("All races after add");
        tryPrintAllRaces();

        race = tryFindRaceById(race.getId());
        if (race == null) {
            System.out.println("Failed to retrieve race");
            System.exit(-1);
        }
        System.out.println("Found: " + race);


        race = tryUpdateRace(race.getId(), "FANCY_CYCLING_CHANGED", 2);
        if (race == null) {
            System.out.println("Failed to update race");
            System.exit(-1);
        }
        System.out.println("Updated: " + race);

        System.out.println("All races after update");
        tryPrintAllRaces();

        race = tryDeleteRace(race.getId());
        if (race == null) {
            System.out.println("Failed to delete race");
            System.exit(-1);
        }
        System.out.println("Deleted: " + race);

        System.out.println("All races after delete");
        tryPrintAllRaces();
    }
}
