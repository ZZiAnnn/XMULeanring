import java.util.Iterator;

public abstract class Entry implements Acceptor {
    public abstract String getName();                                   // ȡ���ļ���
    public abstract int getSize();                                      // ȡ���ļ�����
    public Entry add(Entry entry) throws FileTreatmentException {       // ���������
        throw new FileTreatmentException();
    }
    public Iterator iterator() throws FileTreatmentException {    // ����Iterator
        throw new FileTreatmentException();
    }
    public String toString() {                                          // ��ӡ�ִ�
        return getName() + " (" + getSize() + ")";
    }
}

