public class Main {
    public static void main(String[] args) {
        BookShelf bookShelf = new BookShelf(4);
        bookShelf.appendBook(new Book("Around the World in 80 Days"));
        bookShelf.appendBook(new Book("Bible"));
        bookShelf.appendBook(new Book("Forrest Gump"));
        bookShelf.appendBook(new Book("Triumph"));
        //����ֵ��ָ����BookShelfIterator�����
        //����ָ����Iterator�����
        //��Ϊ���ǲ�������shelfIterator�ķ�����д����
        //���Ǵ�������Iterator�ķ�����д����    
        Iterator it = bookShelf.iterator();
        while (it.hasNext()) {
            Book book = (Book)it.next();
            System.out.println("" + book.getName());
        }
    }
}
