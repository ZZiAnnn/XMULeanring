public abstract class Support {
    private String name;                    // �������ߵ�����
    private Support next;                   // ת��λ��
    public Support(String name) {           // ������������
        this.name = name;
    }
    public Support setNext(Support next) {  // �趨ת��λ��
        this.next = next;
        return next;
    }
    public final void support(Trouble trouble) {  // �������Ĳ��E
        if (resolve(trouble)) {
            done(trouble);
        } else if (next != null) {
            next.support(trouble);
        } else {
            fail(trouble);
        }
    }
    public String toString() {              // ��ӡ�ִ�
        return "[" + name + "]";
    }
    protected abstract boolean resolve(Trouble trouble); // ����ķ���
    protected void done(Trouble trouble) {  // �ѽ��
        System.out.println(trouble + " is resolved by " + this + ".");
    }
    protected void fail(Trouble trouble) {  // ��δ���
        System.out.println(trouble.toString() + " cannot be resolved.");
    }
}

