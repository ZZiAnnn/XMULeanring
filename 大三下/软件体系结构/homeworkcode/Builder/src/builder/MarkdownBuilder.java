package builder;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class MarkdownBuilder extends Builder{
    private String filename;                           // 产生的文件名
    private PrintWriter writer;                        // 写入到文件的PrintWriter
    public void makeTitle(String title) {              // Markdown文件的标题
        filename = title + ".md";                      // 根据标题決定文件名
        try {
            writer = new PrintWriter(new FileWriter(filename));  // 建立PrintWriter
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 输出标题
        writer.println("# " + title);
    }
    public void makeString(String str) {               // Markdown文件的字串
        writer.println(str);
    }
    public void makeItems(String[] items) {            // HTML文件的项目
        for (String item : items) {
            writer.println("* " + item);
        }
        writer.println("");
    }
    public Object getResult() {                        // 完成的文件
        writer.close();                                // 关闭文件
        return filename;                               // 返回文件名
    }
}
