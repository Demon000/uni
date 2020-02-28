package domain;

public interface ISerializer<ID, E extends BaseEntity<ID>, F> {
    F serialize(E entity);
    E deserialize(F value);
}
