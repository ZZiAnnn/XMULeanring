public abstract class AbstractDisplay { // ������AbstractDisplay
    public abstract void open();        // ������ʵ�ֵĳ��󷽷���1��open
    public abstract void print();       // ������ʵ�ֵĳ��󷽷���2��print
    public abstract void close();       // ������ʵ�ֵĳ��󷽷���3��close
    public final void display() {       // �ڴ˳�������ʵ�ֵķ���display
        open();                         // ��open��
        for (int i = 0; i < 5; i++) {   // ����5��print��
          print();
        }
        close();         // �����close���������ʵ��display����ʱ�ă���
    }
}

