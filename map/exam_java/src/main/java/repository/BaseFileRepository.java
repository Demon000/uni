package repository;

import domain.BaseEntity;
import domain.ISerializer;

public abstract class BaseFileRepository<ID, E extends BaseEntity<ID>, F, S extends ISerializer<ID, E, F>>
        extends BaseRepository<ID, E> implements IRepository<ID, E> {
    protected final S serializer;
    protected final String filePath;

    public BaseFileRepository(String filePath, S serializer) {
        this.filePath = filePath;
        this.serializer = serializer;
    }

    protected abstract void readFromFile();
    protected abstract void writeToFile();

    @Override
    public E find(ID id) {
        readFromFile();
        return super.find(id);
    }

    @Override
    public Iterable<E> find() {
        readFromFile();
        return super.find();
    }

    @Override
    public E add(E entity) {
        readFromFile();
        E result = super.add(entity);
        writeToFile();
        return result;
    }

    @Override
    public E update(E entity) {
        readFromFile();
        E result = super.update(entity);
        writeToFile();
        return result;
    }

    @Override
    public E remove(ID id) {
        readFromFile();
        E result = super.remove(id);
        writeToFile();
        return result;
    }

    @Override
    public void empty() {
        super.empty();
        writeToFile();
    }
}
