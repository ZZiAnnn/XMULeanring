import java.awt.TextField;
import java.awt.Color;
import java.awt.event.TextListener;
import java.awt.event.TextEvent;

public class ColleagueTextField extends TextField implements TextListener, Colleague {
    private Mediator mediator;
    public ColleagueTextField(String text, int columns) {   // 构造子
        super(text, columns);
    }
    public void setMediator(Mediator mediator) {            // 保留Mediator
        this.mediator = mediator;
    }
    public void setColleagueEnabled(boolean enabled) {      // Mediator指示有效／无效
        setEnabled(enabled);
        setBackground(enabled ? Color.white : Color.lightGray);
    }
    public void textValueChanged(TextEvent e) {             // 若字串有变化，则通知Mediator
        mediator.colleagueChanged(this);//TextValue有变化了，去咨询中介
    }
}

