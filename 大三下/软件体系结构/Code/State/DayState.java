//ר�������������
public class DayState implements State {
    private static DayState singleton = new DayState();
    private DayState() {                                // ������Ϊprivate
    }
    public static State getInstance() {                 // ȡ��Ψһ��ʵ��
        return singleton;
    }
    public void doClock(Context context, int hour) {    // �趨ʱ��
        if (hour < 9 || 17 <= hour) {
            context.changeState(NightState.getInstance());//Ϊ�β���New NightState��
        }
    }
    public void doUse(Context context) {                // ʹ�ý��
        context.recordLog("ʹ�ý��(����)");
    }
    public void doAlarm(Context context) {              // ����
        context.callSecurityCenter("����(����)");
    }
    public void doPhone(Context context) {              // һ��ͨ��
        context.callSecurityCenter("һ���ͨ��(����)");
    }
    public String toString() {                          // ����ִ�
        return "[����]";
    }
}

