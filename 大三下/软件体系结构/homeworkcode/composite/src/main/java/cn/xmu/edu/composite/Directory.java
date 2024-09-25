package cn.xmu.edu.composite;

import java.util.Iterator;
import java.util.Vector;

public class Directory extends Entry {
    private String name;                      // 目錄名稱
    private Vector directory = new Vector();  // 目錄进入点的集合
    public Directory(String name) {           // 建構子
        this.name = name;
    }
    public String getName() {                 // 取得目錄名稱
        return name;
    }
    public int getSize() {                    // 取得目錄容量
        int size = 0;
        Iterator it = directory.iterator();
        while (it.hasNext()) {
            Entry entry = (Entry)it.next();
            size+= entry.getSize();
        }
        return size;
    }
    public Entry add(Entry entry) {          // 新增进入点
        directory.add(entry);
        return this;
    }

    protected String printList(String prefix) {// 进入点的总览
        StringBuilder res = new StringBuilder(prefix + "/" + this + "\n");
        Iterator it = this.directory.iterator();

        while(it.hasNext()) {
            Entry entry = (Entry)it.next();
            res.append(entry.printList(prefix + "/" + this.name));
        }
        return res.toString();
    }

    public Vector getDirectory() {
        return this.directory;
    }
}


