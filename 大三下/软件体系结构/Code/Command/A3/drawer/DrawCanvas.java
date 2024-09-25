package drawer;

import command.*;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class DrawCanvas extends Canvas implements Drawable {
    // ����ɫ��
    private Color color = Color.red;
    // ���Ƶ�İ뾶
    private int radius = 6;
    // ��¼
    private MacroCommand history;
    // ������
    public DrawCanvas(int width, int height, MacroCommand history) {
        setSize(width, height);
        setBackground(Color.white);
        this.history = history;
    }
    // �ٶȻ���������¼
    public void paint(Graphics g) {
        history.execute();
    }
    // ����
    public void draw(int x, int y) {
        Graphics g = getGraphics();
        g.setColor(color);
        g.fillOval(x - radius, y - radius, radius * 2, radius * 2);
    }
}

