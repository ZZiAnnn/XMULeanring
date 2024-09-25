package Iterator1;

//实现Iterator接口即可将BookShelfIterator视为Iterator进行处理
public class BookShelfIterator implements Iterator {
    private BookShelf bookShelf;
    private int index;
    public BookShelfIterator(BookShelf bookShelf) {
        this.bookShelf = bookShelf;
        this.index = 0;
    }
    public boolean hasNext() {
        int idx = index;
        while(idx < bookShelf.getLength() && ! bookShelf.getBookAt(idx).getName().startsWith("A")) idx++;
        return idx < bookShelf.getLength();
    }
    //next方法返回目前该书（Book的对象实例），然后把index推到下一个为位置
    public Object next() {
        while(index < bookShelf.getLength() && ! bookShelf.getBookAt(index).getName().startsWith("A")) index++;
        return bookShelf.getBookAt(index++);
    }
}

