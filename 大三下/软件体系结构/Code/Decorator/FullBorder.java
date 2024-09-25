public class FullBorder extends Border {
    public FullBorder(Display display) {
        super(display);
    }
    public int getColumns() {                   // 字数＝內容字数＋內容两边的装饰字符
        return 1 + display.getColumns() + 1;
    }
    public int getRows() {                      // 行数＝內容行数＋上下的装饰字符
        return 1 + display.getRows() + 1;
    }
    public String getRowText(int row) {         // 指定该行的內容
        if (row == 0) {                                                 // 外框顶端
            return "+" + makeLine('-', display.getColumns()) + "+";
        } else if (row == display.getRows() + 1) {                      // 外框底部
            return "+" + makeLine('-', display.getColumns()) + "+";
        } else {                                                        // 其他部分
            return "|" + display.getRowText(row - 1) + "|";
        }
    }
    private String makeLine(char ch, int count) {         // 以字符ch，建立重复count次的连续字串
        StringBuffer buf = new StringBuffer();
        for (int i = 0; i < count; i++) {
            buf.append(ch);
        }
        return buf.toString();
    }
}

