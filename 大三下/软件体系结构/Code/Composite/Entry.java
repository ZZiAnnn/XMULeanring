public abstract class Entry {
     public abstract String getName();					// ȡ���ļ���
     public abstract int getSize();					// ȡ���ļ�����
     //public Entry e1;
     public Entry add(Entry entry) throws FileTreatmentException {	// ���������
         throw new FileTreatmentException();
     }
     public void printList() {						// �������
         printList("");
     }
     protected abstract void printList(String prefix);			// ��ǰ�����prefix��
									// �������
     public String toString() {						// �ִ������ʽ
         return getName() + " (" + getSize() + ")";
     }
} 
