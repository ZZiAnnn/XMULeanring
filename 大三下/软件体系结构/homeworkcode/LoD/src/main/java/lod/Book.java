package lod;

public class Book {
    private Author author;
    private String title;

    public Book(String title, Author author) {
        this.title = title;
        this.author = author;
    }
    public Author getAuthor() {
        return author;
    }
    public String getAuthorName() {
        return author.getName();
    }

    public String getTitle() {
        return title;
    }
}
