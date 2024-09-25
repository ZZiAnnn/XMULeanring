package Iterator1;

public interface Iterator {
    //hasNext方法用于检查有无下一个元素
    public abstract boolean hasNext();
    //next方法返回聚合当中的一个元素
    public abstract Object next();
}
