public class NoSupport extends Support {
    public NoSupport(String name) {
        super(name);
    }
    protected boolean resolve(Trouble trouble) {     // ����ķ���
        return false; // �Լ���������
    }
}

