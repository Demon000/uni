package repository;

import domain.Book;
import org.apache.logging.log4j.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class BooksRepository {
    private static final Logger logger = LogManager.getLogger();
    private Connection connection;

    public BooksRepository(Connection connection) {
        this.connection = connection;
        logger.info("Connected.");
    }

    public void add(Book book) throws SQLException {
        PreparedStatement statement =
                connection.prepareStatement("insert into Books(Title, Author, Price) values (?, ?, ?)");
        statement.setString(1, book.getTitle());
        statement.setString(2, book.getAuthor());
        statement.setFloat(3, book.getPrice());
        statement.execute();
        logger.info("Added book.");
    }

    public List<Book> findAll() throws SQLException {
        Statement statement = connection.createStatement();
        ResultSet results = statement.executeQuery("select * from Books");
        List<Book> books = new ArrayList<>();
        while (results.next()) {
            Book book = new Book(results.getString("Title"),
                    results.getString("Author"),
                    results.getFloat("Price"));
            books.add(book);
        }

        logger.info("Found all books.");

        return books;
    }

    public void updateBookPrice(Book book) throws SQLException {
        PreparedStatement statement =
                connection.prepareStatement("update Books set Price=? where Title=? and Author = ?");
        statement.setFloat(1, book.getPrice());
        statement.setString(2, book.getTitle());
        statement.setString(3, book.getAuthor());
        statement.execute();
        logger.info("Updated book price.");
    }

    public void deleteBook(Book book) throws SQLException {
        PreparedStatement statement =
                connection.prepareStatement("delete from Books where Title=? and Author = ?");
        statement.setString(1, book.getTitle());
        statement.setString(2, book.getAuthor());
        statement.execute();
        logger.info("Deleted book.");
    }
}
