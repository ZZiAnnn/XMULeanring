public class BigString {
    // ���������֡�������
    private BigChar bigchars[];
    // ������
    public BigString(String string) {
        bigchars = new BigChar[string.length()];//��������
        BigCharFactory factory = BigCharFactory.getInstance();
        for (int i = 0; i < bigchars.length; i++) {
            //�������������ܻ�������Ӧ��ָ��ͬһ�����󣬽�Լ�˿ռ�
            bigchars[i] = factory.getBigChar(string.charAt(i));
        }
    }
    // ��ʾ
    public void print() {
        for (int i = 0; i < bigchars.length; i++) {
            //���Ҫ���12121212121212121212����Ȼ�������20���ַ�����ʵ��
            //�����Ķ���ֻ��2��
            bigchars[i].print();
        }
    }
}

