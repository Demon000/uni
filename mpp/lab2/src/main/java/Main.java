import domain.Book;
import org.apache.logging.log4j.core.Logger;
import repository.BooksRepository;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

public class Main {
    public static void printBooks(BooksRepository repository) {
        try {
            List<Book> books = repository.findAll();
            books.forEach(System.out::println);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        System.out.println();
    }

    public static void addBook(BooksRepository repository, Book book) {
        try {
            repository.add(book);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void updateBookPrice(BooksRepository repository, Book book) {
        try {
            repository.updateBookPrice(book);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void deleteBook(BooksRepository repository, Book book) {
        try {
            repository.deleteBook(book);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Connection connection;
        try {
            connection = DriverManager.getConnection("jdbc:sqlite:/home/demon000/uni/mpp/lab2/books.db");
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        BooksRepository repository = new BooksRepository(connection);

        printBooks(repository);

        Book book = new Book("Monte Cassino", "Sven Hassle", 55.0f);
        addBook(repository, book);
        printBooks(repository);

        book.setPrice(45.0f);
        updateBookPrice(repository, book);
        printBooks(repository);

        deleteBook(repository, book);
        printBooks(repository);
    }
}
