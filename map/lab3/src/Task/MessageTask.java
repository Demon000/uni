package Task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends BaseTask {
    private final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("YYYY-MM-dd HH:mm");
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public MessageTask(String id, String description,
            String message, String from, String to, LocalDateTime date) {
        super(id, description);

        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        String output = String.format("%s %s", message, date.format(timeFormat));
        System.out.println(output);
    }

    @Override
    public String toString() {
        return String.format("MessageTask => id: %s, from: %s, to: %s, date: %s,\n description: %s,\n message: %s",
                id, from, to, date.format(timeFormat),
                description, message);
    }
}
