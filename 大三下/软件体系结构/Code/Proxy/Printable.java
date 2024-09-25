public interface Printable {
    public abstract void setPrinterName(String name);   // 命名
    public abstract String getPrinterName();            // 取得名称
    public abstract void print(String string);          // 输出字串（打印）
}

