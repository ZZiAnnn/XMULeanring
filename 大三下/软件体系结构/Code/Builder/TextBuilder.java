public class TextBuilder extends Builder {
    //这里用String而不用StringBuffer行不行？有何区别？
    private StringBuffer buffer = new StringBuffer();	// 开始在此属性建立文件
    public void makeTitle(String title) {		// 一般文字格式的标题
        buffer.append("==============================\n");	// 花边
        buffer.append("『" + title + "』\n");			// 有『』的标题
        buffer.append("\n");					// 空行
    }
    public void makeString(String str) {		// 一般文字格式的字串
        buffer.append('■' + str + "\n");		// 有■的字串
        buffer.append("\n");				// 空行
    }
    public void makeItems(String[] items) {		// 一般文字格式的项目
        for (int i = 0; i < items.length; i++) {
            buffer.append("?" + items[i] + "\n");	// 有?的项目
        }
        buffer.append("\n");				// 空行
    }
    public Object getResult() {				// 完成的文件
        buffer.append("==============================\n");	// 花边
        return buffer.toString();		// 把StringBuffer转换成String
    }
}

