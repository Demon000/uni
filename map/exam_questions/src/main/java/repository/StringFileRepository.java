package repository;

import domain.BaseEntity;
import domain.ISerializer;

import java.io.*;
import java.util.HashMap;

public class StringFileRepository<ID, E extends BaseEntity<ID>, S extends ISerializer<ID, E, String>>
        extends BaseFileRepository<ID, E, String, S> {
    public StringFileRepository(String filePath, S serializer) {
        super(filePath, serializer);
    }

    protected void readFromBuffer(BufferedReader reader) throws IOException {
        String line;
        while ((line = reader.readLine()) != null) {
            E entity = serializer.deserialize(line);
            if (entity == null) {
                continue;
            }

            entities.put(entity.getId(), entity);
        }
    }

    protected  void writeToBuffer(BufferedWriter writer) throws IOException {
        for (E entity : entities.values()) {
            String line = serializer.serialize(entity);
            if (line == null) {
                continue;
            }

            writer.write(line);
            writer.newLine();
        }
    }

    @Override
    protected void readFromFile() {
        entities = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            readFromBuffer(reader);
        } catch (IOException ignored) {
        }
    }

    @Override
    protected void writeToFile() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writeToBuffer(writer);
        } catch (IOException ignored) {
        }
    }
}
