package repository;

public class RepositoryUtils {
    private static IArbiterRepository arbiterRepository;
    private static IRaceRepository raceRepository;

    public static IArbiterRepository getArbiterRepository() {
        return arbiterRepository;
    }

    public static void setArbiterRepository(IArbiterRepository arbiterRepository) {
        RepositoryUtils.arbiterRepository = arbiterRepository;
    }

    public static IRaceRepository getRaceRepository() {
        return raceRepository;
    }

    public static void setRaceRepository(IRaceRepository raceRepository) {
        RepositoryUtils.raceRepository = raceRepository;
    }
}
