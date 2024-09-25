public class StringDisplay extends Display {
    private String string;                          // 打印的字串
    public StringDisplay(String string) {           // 以参数指定打印的字串
        this.string = string;
    }
    public int getColumns() {                       // 字数
        return string.getBytes().length;
    }
    public int getRows() {                          // 行数为1
        return 1;
    }
    public String getRowText(int row) {             // 仅在row为0时才返回
        if (row == 0) {
            return string;
        } else {
            return null;
        }
    }
}

