public class StringDisplay extends Display {
    private String string;                          // ��ӡ���ִ�
    public StringDisplay(String string) {           // �Բ���ָ����ӡ���ִ�
        this.string = string;
    }
    public int getColumns() {                       // ����
        return string.getBytes().length;
    }
    public int getRows() {                          // ����Ϊ1
        return 1;
    }
    public String getRowText(int row) {             // ����rowΪ0ʱ�ŷ���
        if (row == 0) {
            return string;
        } else {
            return null;
        }
    }
}

