import lod.Author;
import lod.Book;
import lod.Library;

public class Main {
    public static void main(String[] args) {
        Author author1 = new Author("J.K. Rowling");
        Author author2 = new Author("J.R.R. Tolkien");

        Book book1 = new Book("Harry Potter and the Sorcerer's Stone", author1);
        Book book2 = new Book("The Hobbit", author2);

        Library library = new Library();
        library.addBook(book1);
        library.addBook(book2);

        library.printAuthors();  // 输出作者名字
    }
}
