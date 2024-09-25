package command;

import java.util.Stack;
import java.util.Iterator;

public class MacroCommand implements Command {
    // ����ļ���
    private Stack commands = new Stack();
    // ִ��
    public void execute() {
        Iterator it = commands.iterator();
        while (it.hasNext()) {
            ((Command)it.next()).execute();
        }
    }
    // ����
    public void append(Command cmd) {
        if (cmd != this) {
            commands.push(cmd);
        }
    }
    // �h�����һ������
    public void undo() {
        if (!commands.empty()) {
            commands.pop();
        }
    }
    // ȫ���h��
    public void clear() {
        commands.clear();
    }
}

