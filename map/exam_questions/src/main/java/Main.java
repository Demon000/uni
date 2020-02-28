import controller.MainWindowController;
import domain.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repository.AnswerRepository;
import repository.BaseRepository;
import repository.IRepository;
import repository.StringFileRepository;
import service.Service;

import java.util.List;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        AnswerStringSerializer answerStringSerializer = new AnswerStringSerializer();
        AnswerRepository answersRepository = new AnswerRepository("rezultate.txt", answerStringSerializer);
        answersRepository.empty();

        QuestionStringSerializer questionStringSerializer = new QuestionStringSerializer();
        IRepository<Integer, Question> questionsRepository = new StringFileRepository<>("quizes.txt", questionStringSerializer);
        questionsRepository.empty();
        questionsRepository.add(new Question(1, "Care este varianta corecta? (1)", "20", "30", "40", 1,1.5f));
        questionsRepository.add(new Question(2, "Care este varianta corecta? (2)", "20", "30", "40", 2,2.5f));
        questionsRepository.add(new Question(3, "Care este varianta corecta? (3)", "20", "30", "40", 3,3.5f));

        IRepository<Integer, Question> availableQuestionsRepository = new BaseRepository<>();
        IRepository<Integer, Question> askedQuestionsRepository = new BaseRepository<>();

        Iterable<Question> questions = questionsRepository.find();
        for (Question question : questions) {
            availableQuestionsRepository.add(question);
        }

        IRepository<String, Student> studentsRepository = new BaseRepository<>();
        studentsRepository.empty();
        studentsRepository.add(new Student("Teodor Spiridon"));
        studentsRepository.add(new Student("Mihai Solcan"));
        studentsRepository.add(new Student("Cosmin Tanislav"));

        Service service = new Service(answersRepository, availableQuestionsRepository,
                askedQuestionsRepository, studentsRepository);

        MainWindowController mainWindowController = new MainWindowController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(MainWindowController.VIEW_NAME));
        loader.setController(mainWindowController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(MainWindowController.VIEW_TITLE);
        primaryStage.show();
    }
}
