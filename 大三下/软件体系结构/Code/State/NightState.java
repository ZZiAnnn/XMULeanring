public class NightState implements State {
    private static NightState singleton = new NightState();
    private NightState() {                              // 构造子为private
    }
    public static State getInstance() {                 // 取得唯一的实例
        return singleton;
    }
    public void doClock(Context context, int hour) {    // 设定时间
        if (9 <= hour && hour < 17) {
            context.changeState(DayState.getInstance());
        }
    }
    public void doUse(Context context) {                // 使用金库
        context.callSecurityCenter("异常：晚间使用金库！");
    }
    public void doAlarm(Context context) {              // 警铃
        context.callSecurityCenter("警铃(晚间)");
    }
    public void doPhone(Context context) {              // 一般通话
        context.recordLog("晚间的通话录音");
    }
    public String toString() {                          // 输出字串
        return "[晚间]";
    }
}

