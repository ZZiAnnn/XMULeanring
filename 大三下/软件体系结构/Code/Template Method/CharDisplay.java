public class CharDisplay extends AbstractDisplay {  // CharDisplay是AbstractDisplay
                                             // 的子类。
    private char ch;		// 应该输出的字符。
    public CharDisplay(char ch) {	// 把以构造子传递过来的字符ch
        this.ch = ch;	// 储存在属性内。
    }
    public void open() {	// 本来在父类是抽象方法。
	// 这里过载（override）后实现。
        System.out.print("<<");	// 输出"<<"做为开始字串。
    }
    public void print() {	// print方法也是在此实现。它是从display
				// 被重复调用出来。
        System.out.print(ch);	// 输出1个储存在属性内的字符。
    }
    public void close() {	// close方法也是在此实现。
        System.out.println(">>");	// 输出结束字串">>"。
    }
}

