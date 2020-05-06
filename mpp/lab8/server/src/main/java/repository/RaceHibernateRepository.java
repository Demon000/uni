package repository;

import domain.Race;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import javax.persistence.TypedQuery;
import java.util.List;

public class RaceHibernateRepository extends HibernateRepository implements IRaceRepository {
    public RaceHibernateRepository(SessionFactory sessionFactory) {
        super(sessionFactory);
    }

    @Override
    public void add(Race race) throws RepositoryError {
        runWithTransaction(session -> {
            session.save(race);
        });
    }

    @Override
    public Race findById(int id) throws RepositoryError {
        Session session;
        Race race;

        try {
            session = sessionFactory.openSession();
            race = session.get(Race.class, id);

            logger.info("Retrieved race");

            return race;
        } catch (Exception e) {
            logger.error("Failed to retrieve race");
            logger.error(e);
            throw new RepositoryError("Failed to retrieve race");
        }
    }

    @Override
    public List<Race> find() throws RepositoryError {
        List<Race> races;
        Session session;

        try {
            String command = "from domain.Race";
            session = sessionFactory.openSession();
            TypedQuery<Race> query = session.createQuery(command, Race.class);
            races = query.getResultList();

            logger.info("Retrieved races");
            logger.info(command);

            return races;
        } catch (Exception e) {
            logger.error("Failed to retrieve races");
            logger.error(e);
            throw new RepositoryError("Failed to retrieve races");
        }
    }

    @Override
    public void update(Race race) throws RepositoryError {
        runWithTransaction(session -> {
            session.update(race);
        });
    }

    @Override
    public void delete(Race race) throws RepositoryError {
        runWithTransaction(session -> {
            session.delete(race);
        });
    }
}
