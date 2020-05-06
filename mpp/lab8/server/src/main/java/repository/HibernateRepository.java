package repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

public abstract class HibernateRepository {
    protected final Logger logger = LogManager.getLogger();
    protected final SessionFactory sessionFactory;

    public HibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    protected interface TransactionProtectedRunner {
        void run(Session session);
    }

    protected void runWithTransaction(TransactionProtectedRunner runner) throws RepositoryError {
        Session session = null;

        try {
            session = sessionFactory.openSession();
            session.beginTransaction();
            runner.run(session);
            session.getTransaction().commit();

            logger.info("Transaction committed");
        } catch (Exception e) {
            if (session != null && session.getTransaction() != null) {
                session.getTransaction().rollback();
            }

            logger.error("Failed to commit transaction");
            logger.error(e);
            throw new RepositoryError(e);
        }
    }
}
