public abstract class Display {
    public abstract int getColumns();               // 取得横向的字数
    public abstract int getRows();                  // 取得直向的行数
    public abstract String getRowText(int row);     // 取得第row个字串
    public final void show() {                      // 打印所有內容
        for (int i = 0; i < getRows(); i++) {
            System.out.println(getRowText(i));
        }
    }
}

