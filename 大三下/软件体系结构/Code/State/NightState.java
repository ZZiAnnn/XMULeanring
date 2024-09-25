public class NightState implements State {
    private static NightState singleton = new NightState();
    private NightState() {                              // ������Ϊprivate
    }
    public static State getInstance() {                 // ȡ��Ψһ��ʵ��
        return singleton;
    }
    public void doClock(Context context, int hour) {    // �趨ʱ��
        if (9 <= hour && hour < 17) {
            context.changeState(DayState.getInstance());
        }
    }
    public void doUse(Context context) {                // ʹ�ý��
        context.callSecurityCenter("�쳣�����ʹ�ý�⣡");
    }
    public void doAlarm(Context context) {              // ����
        context.callSecurityCenter("����(���)");
    }
    public void doPhone(Context context) {              // һ��ͨ��
        context.recordLog("����ͨ��¼��");
    }
    public String toString() {                          // ����ִ�
        return "[���]";
    }
}

