public interface Context {
    public abstract void setClock(int hour);                // 设定时间
    public abstract void changeState(State state);          // 状态变化
    public abstract void callSecurityCenter(String msg);    // 呼叫保安中心
    public abstract void recordLog(String msg);             // 保安中心保留记录
}

