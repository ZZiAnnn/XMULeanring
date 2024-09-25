public class Main {
    public static void main(String[] args) {
        BookShelf bookShelf = new BookShelf(4);
        bookShelf.appendBook(new Book("Around the World in 80 Days"));
        bookShelf.appendBook(new Book("Bible"));
        bookShelf.appendBook(new Book("Forrest Gump"));
        bookShelf.appendBook(new Book("Triumph"));
        //返回值不指定到BookShelfIterator类变量
        //而是指定到Iterator类变量
        //因为我们不是利用shelfIterator的方法来写程序
        //而是打算利用Iterator的方法来写程序    
        Iterator it = bookShelf.iterator();
        while (it.hasNext()) {
            Book book = (Book)it.next();
            System.out.println("" + book.getName());
        }
    }
}
