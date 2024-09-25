public class SideBorder extends Border {
    private char borderChar;                        // 装饰字符
    public SideBorder(Display display, char ch) {   // 以构造子指定Display和装饰字符 
        super(display);
        this.borderChar = ch;
    }
    public int getColumns() {                       // 字数要再加上內容两边的装饰字符
        return 1 + display.getColumns() + 1;
    }
    public int getRows() {                          // 行数同內容的行数
        return display.getRows();
    }
    public String getRowText(int row) {             // 指定该行的內容即为在內容之指定行的两边
						    // 加上装饰字符

        return borderChar + display.getRowText(row) + borderChar;
    }
}

