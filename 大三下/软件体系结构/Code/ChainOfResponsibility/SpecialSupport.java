public class SpecialSupport extends Support {
    private int number;                                 // ֻ�ܽ���˺��������
    public SpecialSupport(String name, int number) {    // ������
        super(name);
        this.number = number;
    }
    protected boolean resolve(Trouble trouble) {     // ����ķ���
        if (trouble.getNumber() == number) {
            return true;
        } else {
            return false;
        }
    }
}

