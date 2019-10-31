package Runner;

public class DelayTaskRunner extends AbstractTaskRunner {
    private final int DELAY = 3000;

    public DelayTaskRunner(ITaskRunner tr) {
        super(tr);
    }

    @Override
    public void executeOneTask() {
        try {
            Thread.sleep(DELAY);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        tr.executeOneTask();
    }
}
