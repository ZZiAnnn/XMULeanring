import java.util.Iterator;
import java.util.Vector;

public class Directory extends Entry {
    private String name;                    // Ŀ¼����
    private Vector dir = new Vector();      // Ŀ¼�����ļ���
    public Directory(String name) {         // ������
        this.name = name;
    }
    public String getName() {               // ȡ������
        return name;
    }
    public int getSize() {                  // ȡ��Ŀ¼����
        int size = 0;
        Iterator it = dir.iterator();
        while (it.hasNext()) {
            Entry entry = (Entry)it.next();
            size += entry.getSize();
        }
        return size;
    }
    public Entry add(Entry entry) {         // ���������
        dir.add(entry);
        return this;
    }
    public Iterator iterator() {      // ����Iterator 
        return dir.iterator();
    }
    public void accept(Visitor v) {         // ���ܷÿ�
        v.visit(this);
    }
}

