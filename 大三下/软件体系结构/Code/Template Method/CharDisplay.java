public class CharDisplay extends AbstractDisplay {  // CharDisplay��AbstractDisplay
                                             // �����ࡣ
    private char ch;		// Ӧ��������ַ���
    public CharDisplay(char ch) {	// ���Թ����Ӵ��ݹ������ַ�ch
        this.ch = ch;	// �����������ڡ�
    }
    public void open() {	// �����ڸ����ǳ��󷽷���
	// ������أ�override����ʵ�֡�
        System.out.print("<<");	// ���"<<"��Ϊ��ʼ�ִ���
    }
    public void print() {	// print����Ҳ���ڴ�ʵ�֡����Ǵ�display
				// ���ظ����ó�����
        System.out.print(ch);	// ���1�������������ڵ��ַ���
    }
    public void close() {	// close����Ҳ���ڴ�ʵ�֡�
        System.out.println(">>");	// ��������ִ�">>"��
    }
}

