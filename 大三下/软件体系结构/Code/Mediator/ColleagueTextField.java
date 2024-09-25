import java.awt.TextField;
import java.awt.Color;
import java.awt.event.TextListener;
import java.awt.event.TextEvent;

public class ColleagueTextField extends TextField implements TextListener, Colleague {
    private Mediator mediator;
    public ColleagueTextField(String text, int columns) {   // ������
        super(text, columns);
    }
    public void setMediator(Mediator mediator) {            // ����Mediator
        this.mediator = mediator;
    }
    public void setColleagueEnabled(boolean enabled) {      // Mediatorָʾ��Ч����Ч
        setEnabled(enabled);
        setBackground(enabled ? Color.white : Color.lightGray);
    }
    public void textValueChanged(TextEvent e) {             // ���ִ��б仯����֪ͨMediator
        mediator.colleagueChanged(this);//TextValue�б仯�ˣ�ȥ��ѯ�н�
    }
}

