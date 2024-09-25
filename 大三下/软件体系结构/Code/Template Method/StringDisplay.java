public class StringDisplay extends AbstractDisplay {  // StringDisplayҲ��
                                                        // AbstractDisplay�����ࡣ
    private String string;                    // Ӧ������ִ���
    private int width;                        // ��byteΪ��λ��������ִ�����ȡ���
    public StringDisplay(String string) {     // ���Թ����Ӵ��ݹ������ִ�string
        this.string = string;                 // ���������ԃȡ�
        this.width = string.getBytes().length;// ���Ű���byteΪ��λ����Ԫ���
        //System.out.println(this.width);                                      // ���������ԣ������ʹ�õ���
    }
    public void open() {                      // �ȸ�д���ٶ����open������
        printLine();                          // �Դ���ķ���printLine
                                              // �����߶Ρ�
    }
    public void print() {                        // print��������
        System.out.println("|" + string + "|");  // ������������ִ�ǰ��
                                                 //����"|"��Ȼ����������档
    }
    public void close() {		// close������ͬ
        printLine();			// open������printLine���������߶Ρ�
        //System.out.println(width);
    }
    private void printLine() {		// ����open��close�����õ�printLine������
					// ��Ϊ����private������ֻ���ڴ����Ȳ�ʹ�á�
        System.out.print("+");		// ���"+"�Ǻű�ʾ�߿�λ�á�
        for (int i = 0; i < width; i++) {	// ���width��"-"��
            System.out.print("-");		// �����߶Ρ�
        }
        System.out.println("+");		//���"+"�Ǻű�ʾ�߿�λ�á�
    }
}

