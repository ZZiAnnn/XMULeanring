public class Book {
    private String name = "";
    //构造函数指定书名
    public Book(String name) {
        this.name = name;
    }
    //对外接口返回书名
    public String getName() {
        return name;
    }
}
