public class PrinterProxy implements Printable {
    private String name;            // 命名
    private Printer real;           // 「本人」
    public PrinterProxy() {
    }
    public PrinterProxy(String name) {      // 构造子
        this.name = name;
    }
    public synchronized void setPrinterName(String name) {  // 命名
        if (real != null) {
            real.setPrinterName(name);  // 「本人」也要命名
        }
        this.name = name;
    }
    public String getPrinterName() {    // 取得名称
        return name;
    }
    public void print(String string) {  // 输出
        realize();
        real.print(string);
    }
    private synchronized void realize() {   // 产生「本人」
        if (real == null) {
            real = new Printer(name);
        }
    }
}

