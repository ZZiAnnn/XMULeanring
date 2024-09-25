import java.util.Iterator;

public abstract class Entry implements Acceptor {
    public abstract String getName();                                   // 取得文件名
    public abstract int getSize();                                      // 取得文件容量
    public Entry add(Entry entry) throws FileTreatmentException {       // 新增进入点
        throw new FileTreatmentException();
    }
    public Iterator iterator() throws FileTreatmentException {    // 产生Iterator
        throw new FileTreatmentException();
    }
    public String toString() {                                          // 打印字串
        return getName() + " (" + getSize() + ")";
    }
}

