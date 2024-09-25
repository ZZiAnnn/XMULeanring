import java.util.Iterator;

public class ListVisitor extends Visitor {
    private String currentdir = "";                         // Ŀǰ���ڵ�Ŀ¼����
    public void visit(File file) {                  // �����ļ�ʱ������
        System.out.println(currentdir + "/" + file);
    }
    public void visit(Directory directory) {   // ����Ŀ¼ʱ������
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

