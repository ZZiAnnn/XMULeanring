package cn.xmu.edu.composite;


public abstract class Entry {
    public abstract String getName();					// 取得文件名
    public abstract int getSize();					// 取得文件容量
    //public Entry e1;
    public Entry add(Entry entry) throws FileTreatmentException {	// 新增进入点
        throw new FileTreatmentException();
    }
    public String printList() {						// 输出总览
        return printList("");
    }
    protected abstract String printList(String prefix);			// 在前面加上prefix后
    // 输出总览
    public String toString() {						// 字串输出格式
        return getName() + " (" + getSize() + ")";
    }
} 
