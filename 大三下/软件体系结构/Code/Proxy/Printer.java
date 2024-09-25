public class Printer implements Printable {
    private String name;
    public Printer() {
        heavyJob("正在产生Printer的对象实例");
    }
    public Printer(String name) {                   // 构造子
        this.name = name;
        heavyJob("正在产生Printer的对象实例(" + name + ")");
    }
    public void setPrinterName(String name) {       // 命名
        this.name = name;
    }
    public String getPrinterName() {                // 取得名称
        return name;
    }
    public void print(String string) {              // 输出名称
        System.out.println("=== " + name + " ===");
        System.out.println(string);
    }
    private void heavyJob(String msg) {             // 较重的工作（假设）
        System.out.print(msg);
        for (int i = 0; i < 5; i++) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
            }
            System.out.print(".");
        }
        System.out.println("完成。");
    }
}

