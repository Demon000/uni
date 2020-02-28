package repository;

import domain.Answer;
import domain.AnswerStringSerializer;

import java.io.*;
import java.util.HashMap;

public class AnswerRepository extends StringFileRepository<String, Answer, AnswerStringSerializer> {
    private float maxPoints = 0.0f;

    public AnswerRepository(String filePath, AnswerStringSerializer serializer) {
        super(filePath, serializer);
    }

    public void setMaxPoints(float maxPoints) {
        this.maxPoints = maxPoints;
        writeToFile();
    }

    @Override
    protected void readFromFile() {
        entities = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String maxPointsString = reader.readLine();
            this.maxPoints = Float.parseFloat(maxPointsString);
            readFromBuffer(reader);
        } catch (IOException ignored) {
        }
    }

    @Override
    protected void writeToFile() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write(String.valueOf(maxPoints));
            writer.newLine();
            writeToBuffer(writer);
        } catch (IOException ignored) {
        }
    }
}
