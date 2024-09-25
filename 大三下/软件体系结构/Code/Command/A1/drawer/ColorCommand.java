package drawer;

import command.Command;
import java.awt.Color;

public class ColorCommand implements Command {
    // 绘制对象
    protected Drawable drawable;
    // 绘制色彩
    private Color color;
    // 构造子
    public ColorCommand(Drawable drawable, Color color) {
        this.drawable = drawable;
        this.color = color;
    }
    // 执行
    public void execute() {
        drawable.setColor(color);
    }
}

