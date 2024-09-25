//专心做白天的事情
public class DayState implements State {
    private static DayState singleton = new DayState();
    private DayState() {                                // 构造子为private
    }
    public static State getInstance() {                 // 取得唯一的实例
        return singleton;
    }
    public void doClock(Context context, int hour) {    // 设定时间
        if (hour < 9 || 17 <= hour) {
            context.changeState(NightState.getInstance());//为何不能New NightState？
        }
    }
    public void doUse(Context context) {                // 使用金库
        context.recordLog("使用金库(白天)");
    }
    public void doAlarm(Context context) {              // 警铃
        context.callSecurityCenter("警铃(白天)");
    }
    public void doPhone(Context context) {              // 一般通话
        context.callSecurityCenter("一般的通话(白天)");
    }
    public String toString() {                          // 输出字串
        return "[白天]";
    }
}

