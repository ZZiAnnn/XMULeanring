public interface Context {
    public abstract void setClock(int hour);                // �趨ʱ��
    public abstract void changeState(State state);          // ״̬�仯
    public abstract void callSecurityCenter(String msg);    // ���б�������
    public abstract void recordLog(String msg);             // �������ı�����¼
}

