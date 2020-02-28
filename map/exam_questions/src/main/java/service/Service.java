package service;

import domain.Answer;
import domain.Question;
import domain.Result;
import domain.Student;
import observer.Observable;
import repository.AnswerRepository;
import repository.IRepository;

import java.util.*;

import static utils.CollectionUtils.listFromIterable;

public class Service extends Observable {
    public AnswerRepository answersRepository;
    public IRepository<Integer, Question> availableQuestionsRepository;
    public IRepository<Integer, Question> askedQuestionsRepository;
    public IRepository<String, Student> studentRepository;

    public Service(AnswerRepository answersRepository,
                   IRepository<Integer, Question> availableQuestionsRepository,
                   IRepository<Integer, Question> askedQuestionsRepository,
                   IRepository<String, Student> studentsRepository) {
        this.answersRepository = answersRepository;
        this.availableQuestionsRepository = availableQuestionsRepository;
        this.askedQuestionsRepository = askedQuestionsRepository;
        this.studentRepository = studentsRepository;
    }

    public boolean isStudentLoggedIn(String name) {
        Student student = studentRepository.find(name);
        if (student == null) {
            return false;
        }

        return student.getLoggedIn();
    }

    public void logStudentIn(String name) {
        Student student = studentRepository.find(name);
        if (student == null) {
            return;
        }

        student.setLoggedIn(true);
        studentRepository.update(student);
    }

    public List<Question> getAvailableQuestions() {
        return listFromIterable(availableQuestionsRepository.find());
    }

    public List<Question> getAskedQuestions() {
        return listFromIterable(askedQuestionsRepository.find());
    }

    public float getMaxPoints() {
        float maxPoints = 0;

        Iterable<Question> questions = askedQuestionsRepository.find();
        for (Question question : questions) {
            maxPoints += question.getPoints();
            System.out.println(question.getPoints());
        }

        return maxPoints;
    }

    public void askQuestion(Integer questionId) {
        Question question = availableQuestionsRepository.find(questionId);
        if (question == null) {
            return;
        }

        availableQuestionsRepository.remove(questionId);
        askedQuestionsRepository.add(question);

        float maxPoints = getMaxPoints();
        answersRepository.setMaxPoints(maxPoints);
        change(ServiceObserverKeys.QUESTION_ASKED, null, question);
    }

    public void answerQuestion(String studentName, Integer questionId, Integer givenChoice) {
        Student student = studentRepository.find(studentName);
        if (student == null) {
            return;
        }

        Question question = askedQuestionsRepository.find(questionId);
        if (question == null) {
            return;
        }

        Answer answer;
        if (question.isCorrectChoice(givenChoice)) {
            answer = new Answer(questionId, studentName, question.getPoints());
        } else {
            answer = new Answer(questionId, studentName, 0.0f);
        }

        answersRepository.add(answer);
        change(ServiceObserverKeys.QUESTION_ANSWERED, null, answer);
    }

    public List<Result> getExamResults() {
        Map<String, Float> sums = new HashMap<>();
        Iterable<Answer> answers = answersRepository.find();
        for (Answer answer : answers) {
            String name = answer.getStudentName();
            sums.putIfAbsent(name, 0.0f);
            sums.put(name, sums.get(name) + answer.getPoints());
        }

        List<Result> results = new ArrayList<>();
        for (Map.Entry<String, Float> entry : sums.entrySet()) {
            Result result = new Result(entry.getKey(), entry.getValue());
            results.add(result);
        }

        return results;
    }

    public void endExam() {
        List<Result> results = getExamResults();
        change(ServiceObserverKeys.EXAM_ENDED, null, results);
    }
}
