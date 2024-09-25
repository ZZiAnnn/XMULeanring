//实现Iterator接口即可将BookShelfIterator视为Iterator进行处理
public class BookShelfIterator implements Iterator {
    private BookShelf bookShelf;
    private int index;
    public BookShelfIterator(BookShelf bookShelf) {
        this.bookShelf = bookShelf;
        this.index = 0;
    }
    public boolean hasNext() {
        if (index < bookShelf.getLength()) {
            return true;
        } else {
            return false;
        }
    }
    //next方法返回目前该书（Book的对象实例），然后把index推到下一个为位置
    public Object next() {
        Book book = bookShelf.getBookAt(index);
        index++;
        return book;
    }
}
