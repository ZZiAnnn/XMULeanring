public class TextBuilder extends Builder {
    //������String������StringBuffer�в��У��к�����
    private StringBuffer buffer = new StringBuffer();	// ��ʼ�ڴ����Խ����ļ�
    public void makeTitle(String title) {		// һ�����ָ�ʽ�ı���
        buffer.append("==============================\n");	// ����
        buffer.append("��" + title + "��\n");			// �С����ı���
        buffer.append("\n");					// ����
    }
    public void makeString(String str) {		// һ�����ָ�ʽ���ִ�
        buffer.append('��' + str + "\n");		// �С����ִ�
        buffer.append("\n");				// ����
    }
    public void makeItems(String[] items) {		// һ�����ָ�ʽ����Ŀ
        for (int i = 0; i < items.length; i++) {
            buffer.append("?" + items[i] + "\n");	// ��?����Ŀ
        }
        buffer.append("\n");				// ����
    }
    public Object getResult() {				// ��ɵ��ļ�
        buffer.append("==============================\n");	// ����
        return buffer.toString();		// ��StringBufferת����String
    }
}

