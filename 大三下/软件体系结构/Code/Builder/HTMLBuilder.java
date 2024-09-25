import java.io.*;

public class HTMLBuilder extends Builder {
    private String filename;                           // 产生的文件名
    private PrintWriter writer;                        // 写入到文件的PrintWriter
    public void makeTitle(String title) {              // HTML文件的标题
        filename = title + ".html";                    // 根据标题決定文件名
        try {
            writer = new PrintWriter(new FileWriter(filename));  // 建立PrintWriter
        } catch (IOException e) {
            e.printStackTrace();
        }
        writer.println("<html><head><title>" + title + "</title></head><body>");
        // 输出标题
        writer.println("<h1>" + title + "</h1>");
    }
    public void makeString(String str) {               // HTML文件的字串
        writer.println("<p>" + str + "</p>");          // 以<p>标签输出
    }
    public void makeItems(String[] items) {            // HTML文件的项目
        writer.println("<ul>");                        // 以<ul>和<li>输出
        for (int i = 0; i < items.length; i++) {
            writer.println("<li>" + items[i] + "</li>");
        }
        writer.println("</ul>");
    }
    public Object getResult() {                        // 完成的文件
        writer.println("</body></html>");              // 关闭标签
        writer.close();                                // 关闭文件
        return filename;                               // 返回文件名
    }
}

