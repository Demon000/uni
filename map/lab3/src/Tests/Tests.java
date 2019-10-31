package Tests;

import Task.MessageTask;
import Task.SortingTask;
import Runner.DelayTaskRunner;
import Runner.PrinterTaskRunner;
import Runner.StrategyTaskRunner;
import Runner.ITaskRunner;
import Utility.SortingStrategy;
import org.junit.Test;

import java.time.LocalDateTime;
import java.util.Vector;

public class Tests {
    private static SortingStrategy sortingStrategy;

    public Tests(String strategyName) {
        try {
            sortingStrategy = SortingStrategy.fromString(strategyName);
        } catch (Exception e) {
            e.printStackTrace();
            sortingStrategy = SortingStrategy.FIFO;
        }
    }

    private void populateTaskRunner(ITaskRunner tr) {
        tr.addTask(new MessageTask("1", "Grade", "You got a 10.", "Mihai", "Ana",
                LocalDateTime.of(2019, 10, 31, 13, 56)));
        tr.addTask(new MessageTask("2", "Grade", "You got a 9.", "Mihai", "Ion",
                LocalDateTime.of(2019, 10, 31, 13, 57)));
        tr.addTask(new MessageTask("3", "Grade", "You got a 9.", "Mihai", "Marcel",
                LocalDateTime.of(2019, 10, 31, 13, 57)));
        tr.addTask(new MessageTask("4", "Grade", "You got a 7.", "Mihai", "Geo",
                LocalDateTime.of(2019, 10, 31, 13, 59)));
        tr.addTask(new MessageTask("5", "Grade", "You got a 5.", "Mihai", "Larisa",
                LocalDateTime.of(2019, 10, 31, 13, 0)));
    }

    @Test
    public void test1() {
        ITaskRunner tr = new StrategyTaskRunner(sortingStrategy);
        populateTaskRunner(tr);
        tr.executeAll();
    }

    @Test
    public void test2() {
        ITaskRunner tr = new DelayTaskRunner(new StrategyTaskRunner(sortingStrategy));
        populateTaskRunner(tr);
        tr.executeAll();
    }

    @Test
    public void test3() {
        ITaskRunner tr = new PrinterTaskRunner(new DelayTaskRunner(new StrategyTaskRunner(sortingStrategy)));
        populateTaskRunner(tr);
        tr.executeAll();
    }

    public void testAll() {
        test1();
        System.out.println();
        test2();
        System.out.println();
        test3();
        System.out.println();
    }
}
