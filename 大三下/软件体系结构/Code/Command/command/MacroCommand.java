package command;

import java.util.Stack;
import java.util.Iterator;

public class MacroCommand implements Command {
    // 命令的集合
    private Stack commands = new Stack();
    // 执行
    public void execute() {
        Iterator it = commands.iterator();
        while (it.hasNext()) {
            ((Command)it.next()).execute();
        }
    }
    // 新增
    public void append(Command cmd) {
        if (cmd != this) {
            commands.push(cmd);
        }
    }
    // 刪除最后一个命令
    public void undo() {
        if (!commands.empty()) {
            commands.pop();
        }
    }
    // 全部刪除
    public void clear() {
        commands.clear();
    }
}

