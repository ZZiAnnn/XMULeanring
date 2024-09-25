public class StringDisplay extends AbstractDisplay {  // StringDisplay也是
                                                        // AbstractDisplay的子类。
    private String string;                    // 应输出的字串。
    private int width;                        // 以byte为单位所求出的字串「宽度」。
    public StringDisplay(String string) {     // 把以构造子传递过来的字串string
        this.string = string;                 // 储存在属性內。
        this.width = string.getBytes().length;// 接着把以byte为单位的字元宽幅
        //System.out.println(this.width);                                      // 储存在属性，后面会使用到。
    }
    public void open() {                      // 先复写后再定义的open方法。
        printLine();                          // 以此类的方法printLine
                                              // 画出线段。
    }
    public void print() {                        // print方法则在
        System.out.println("|" + string + "|");  // 属性所储存的字串前后
                                                 //加上"|"，然后输出到画面。
    }
    public void close() {		// close方法则同
        printLine();			// open，利用printLine方法画出线段。
        //System.out.println(width);
    }
    private void printLine() {		// 这是open和close所调用的printLine方法。
					// 因为这是private，所以只能在此类內部使用。
        System.out.print("+");		// 输出"+"记号表示边框位置。
        for (int i = 0; i < width; i++) {	// 输出width个"-"，
            System.out.print("-");		// 当作线段。
        }
        System.out.println("+");		//输出"+"记号表示边框位置。
    }
}

