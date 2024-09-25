//State接口是一个依据状态而变化的方法的集合
public interface State {
    public abstract void doClock(Context context, int hour);    // 设定时间
    public abstract void doUse(Context context);                // 使用金库
    public abstract void doAlarm(Context context);              // 警铃
    public abstract void doPhone(Context context);              // 一般通话
}

