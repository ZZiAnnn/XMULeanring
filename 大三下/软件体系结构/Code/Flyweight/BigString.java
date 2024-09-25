public class BigString {
    // 「大型文字」的数组
    private BigChar bigchars[];
    // 构造子
    public BigString(String string) {
        bigchars = new BigChar[string.length()];//建立数组
        BigCharFactory factory = BigCharFactory.getInstance();
        for (int i = 0; i < bigchars.length; i++) {
            //下面这条语句可能会产生多个应用指向同一个对象，节约了空间
            bigchars[i] = factory.getBigChar(string.charAt(i));
        }
    }
    // 显示
    public void print() {
        for (int i = 0; i < bigchars.length; i++) {
            //如果要输出12121212121212121212，虽然输出的是20个字符，但实际
            //创建的对象只有2个
            bigchars[i].print();
        }
    }
}

