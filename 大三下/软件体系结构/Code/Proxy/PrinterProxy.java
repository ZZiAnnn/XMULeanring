public class PrinterProxy implements Printable {
    private String name;            // ����
    private Printer real;           // �����ˡ�
    public PrinterProxy() {
    }
    public PrinterProxy(String name) {      // ������
        this.name = name;
    }
    public synchronized void setPrinterName(String name) {  // ����
        if (real != null) {
            real.setPrinterName(name);  // �����ˡ�ҲҪ����
        }
        this.name = name;
    }
    public String getPrinterName() {    // ȡ������
        return name;
    }
    public void print(String string) {  // ���
        realize();
        real.print(string);
    }
    private synchronized void realize() {   // ���������ˡ�
        if (real == null) {
            real = new Printer(name);
        }
    }
}

