import java.util.Iterator;

public class ListVisitor extends Visitor {
    private String currentdir = "";                         // 目前所在的目录名称
    public void visit(File file) {                  // 访问文件时即调用
        System.out.println(currentdir + "/" + file);
    }
    public void visit(Directory directory) {   // 访问目录时即调用
        System.out.println(currentdir + "/" + directory);
        String savedir = currentdir;
        currentdir = currentdir + "/" + directory.getName();
        Iterator it = directory.iterator();
        while (it.hasNext()) {
            Entry entry = (Entry)it.next();
            entry.accept(this);
        }
        currentdir = savedir;
    }
}

