public abstract class Display {
    public abstract int getColumns();               // ȡ�ú��������
    public abstract int getRows();                  // ȡ��ֱ�������
    public abstract String getRowText(int row);     // ȡ�õ�row���ִ�
    public final void show() {                      // ��ӡ���Ѓ���
        for (int i = 0; i < getRows(); i++) {
            System.out.println(getRowText(i));
        }
    }
}

