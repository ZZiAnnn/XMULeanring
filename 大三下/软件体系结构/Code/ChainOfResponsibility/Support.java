public abstract class Support {
    private String name;                    // 问题解决者的名称
    private Support next;                   // 转送位置
    public Support(String name) {           // 产生问题解决者
        this.name = name;
    }
    public Support setNext(Support next) {  // 设定转送位置
        this.next = next;
        return next;
    }
    public final void support(Trouble trouble) {  // 解决问题的步驟
        if (resolve(trouble)) {
            done(trouble);
        } else if (next != null) {
            next.support(trouble);
        } else {
            fail(trouble);
        }
    }
    public String toString() {              // 打印字串
        return "[" + name + "]";
    }
    protected abstract boolean resolve(Trouble trouble); // 解决的方法
    protected void done(Trouble trouble) {  // 已解决
        System.out.println(trouble + " is resolved by " + this + ".");
    }
    protected void fail(Trouble trouble) {  // 尚未解决
        System.out.println(trouble.toString() + " cannot be resolved.");
    }
}

