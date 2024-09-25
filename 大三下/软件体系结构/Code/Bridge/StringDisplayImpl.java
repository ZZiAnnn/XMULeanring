public class StringDisplayImpl extends DisplayImpl {
    private String string;                    
    private int width;                       
    public StringDisplayImpl(String string) { 
        this.string = string;                  
        this.width = string.getBytes().length;                                          
    }
    public void rawOpen() {
        printLine();
    }
    public void rawPrint() {
        System.out.println("|" + string + "|"); // 打印时前后加上"|"。
    }
    public void rawClose() {
        printLine();
    }
    private void printLine() {
        System.out.print("+");                  // 输出框角的"+"记号。
        for (int i = 0; i < width; i++) {       // 输出width个"-"，
            System.out.print("-");              // 做为框线。
        }
        System.out.println("+");                //输出框角的"+"记号。
    }
}

