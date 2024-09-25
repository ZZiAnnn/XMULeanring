public class SideBorder extends Border {
    private char borderChar;                        // װ���ַ�
    public SideBorder(Display display, char ch) {   // �Թ�����ָ��Display��װ���ַ� 
        super(display);
        this.borderChar = ch;
    }
    public int getColumns() {                       // ����Ҫ�ټ��σ������ߵ�װ���ַ�
        return 1 + display.getColumns() + 1;
    }
    public int getRows() {                          // ����ͬ���ݵ�����
        return display.getRows();
    }
    public String getRowText(int row) {             // ָ�����еă��ݼ�Ϊ�ڃ���ָ֮���е�����
						    // ����װ���ַ�

        return borderChar + display.getRowText(row) + borderChar;
    }
}

