package drawer;

import command.Command;
import java.awt.Color;

public class ColorCommand implements Command {
    // ���ƶ���
    protected Drawable drawable;
    // ����ɫ��
    private Color color;
    // ������
    public ColorCommand(Drawable drawable, Color color) {
        this.drawable = drawable;
        this.color = color;
    }
    // ִ��
    public void execute() {
        drawable.setColor(color);
    }
}

