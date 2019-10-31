package Runner;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {
    private final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("YYYY-MM-dd HH:mm");

    public PrinterTaskRunner(ITaskRunner tr) {
        super(tr);
    }

    @Override
    public void executeOneTask() {
        LocalDateTime now = LocalDateTime.now();
        tr.executeOneTask();
        System.out.println(now.format(timeFormat));
    }
}
