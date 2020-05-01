package repository;

import domain.Arbiter;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import javax.persistence.Query;

public class ArbiterHibernateRepository implements IArbiterRepository {
    protected final Logger logger = LogManager.getLogger();
    private final  SessionFactory sessionFactory;

    public ArbiterHibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void add(Arbiter arbiter) throws RepositoryError {
        Transaction transaction = null;
        Session session;

        try {
            session = sessionFactory.openSession();
            transaction = session.beginTransaction();
            session.save(arbiter);
            transaction.commit();

            logger.info("Added arbiter");
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }

            logger.error("Failed to add arbiter");
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public Arbiter findByNameAndPassword(String name, String password) throws RepositoryError {
        Arbiter arbiter;
        Session session;

        try {
            String command =
                    "from domain.Arbiter as A " +
                    "where " +
                        "A.name=:name and " +
                        "A.password=:password";

            session = sessionFactory.openSession();
            Query query = session.createQuery(command);
            query.setParameter("name", name);
            query.setParameter("password", password);
            arbiter = (Arbiter) query.getSingleResult();

            logger.info("Retrieved arbiter");
            logger.info(command);

            return arbiter;
        } catch (Exception e) {
            logger.error("Failed to retrieve arbiter");
            logger.error(e);
            throw new RepositoryError("Failed to retrieve arbiter");
        }
    }
}
