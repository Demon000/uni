package repository;

import domain.Participant;

public interface IParticipantRepository {
    void add(Participant participant) throws RepositoryError;
}
