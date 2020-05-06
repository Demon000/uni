package repository;

import domain.Arbiter;
import domain.Race;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import javax.persistence.TypedQuery;
import java.util.List;

public class ArbiterHibernateRepository extends HibernateRepository implements IArbiterRepository {
    public ArbiterHibernateRepository(SessionFactory sessionFactory) {
        super(sessionFactory);
    }

    @Override
    public void add(Arbiter arbiter) throws RepositoryError {
        runWithTransaction(session -> {
            session.save(arbiter);
        });
    }

    @Override
    public Arbiter findById(int id) throws RepositoryError {
        Session session;
        Arbiter arbiter;

        try {
            session = sessionFactory.openSession();
            arbiter = session.get(Arbiter.class, id);

            logger.info("Retrieved arbiter");

            return arbiter;
        } catch (Exception e) {
            logger.error("Failed to retrieve arbiter");
            logger.error(e);
            throw new RepositoryError("Failed to retrieve arbiter");
        }
    }

    @Override
    public List<Arbiter> find() throws RepositoryError {
        List<Arbiter> arbiters;
        Session session;

        try {
            String command = "from domain.Arbiter";
            session = sessionFactory.openSession();
            TypedQuery<Arbiter> query = session.createQuery(command, Arbiter.class);
            arbiters = query.getResultList();

            logger.info("Retrieved arbiters");
            logger.info(command);

            return arbiters;
        } catch (Exception e) {
            logger.error("Failed to retrieve arbiters");
            logger.error(e);
            throw new RepositoryError("Failed to retrieve arbiters");
        }
    }
}
