public class Trouble {
    private int number;             // 问题编号
    public Trouble(int number) {    // 发生问题
        this.number = number;
    }
    public int getNumber() {        // 取得问题编号
        return number;
    }
    public String toString() {      // 打印显示问题的字串
        return "[Trouble " + number + "]";
    }
}

