public abstract class Node {
    public abstract void parse(Context context) throws ParseException;
}
//仅仅声明方法，并且该方法可能会抛出例外
//具体的方法parse 解析则交由子类去实现，即子类的责任。