//State�ӿ���һ������״̬���仯�ķ����ļ���
public interface State {
    public abstract void doClock(Context context, int hour);    // �趨ʱ��
    public abstract void doUse(Context context);                // ʹ�ý��
    public abstract void doAlarm(Context context);              // ����
    public abstract void doPhone(Context context);              // һ��ͨ��
}

